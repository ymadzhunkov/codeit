// =====================================================================================
//        Created:   4.11.2016 11,29,54
//       Compiler:  g++
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
// =====================================================================================

#include <cstdint>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstring>
#include <random>

struct Point2D {
    explicit Point2D(const unsigned int x, const unsigned int y);
    unsigned int x;
    unsigned int y;
    friend bool operator==(const Point2D &a, const Point2D &b);
};

struct Configuration {
    Configuration(const char *str);
    char mapping[26];
    Configuration(const Configuration &conf, uint32_t mutation);
};

struct Fingers {
    int left, right;
};

class Keyboard {
  public:
    Keyboard(const Configuration mapping);
    int distance(const char *input, const int len,
                 const Fingers &fingers) const;
    Point2D getPosition(const char key) const;
    int getKeyIndex(const char key) const;
    int getFirstKeyIndex(const char *input, const int len) const;
    int getSecondKeyIndex(const char *input, const int len,
                          const int firstKey) const;
    Point2D getKeyByIndex(const int index) const;
    Fingers initPosition(const char *input, const int len) const;
    bool isLeft(const int key1, const int key2) const;
    int dist(const int key1, const int key2) const;
    const Configuration &getConfiguration() const {
        return configuration;
    }

  private:
    Configuration configuration;
};

class Solution {
  public:
    Solution(const Configuration configuration, const char *input,
             const int len)
        : keyboard(configuration),
          fingers(keyboard.initPosition(input, len)), input(input),
          len(len), dist(keyboard.distance(input, len, fingers)) {}

    Solution(const Solution &sol, uint32_t mutation);
    Solution &operator=(const Solution &sol);
    Keyboard keyboard;
    Fingers fingers;
    const char *input;
    const int len;
    int dist;
};

Point2D::Point2D(const unsigned int x_, const unsigned int y_)
    : x(x_), y(y_) {}

bool operator==(const Point2D &a, const Point2D &b) {
    return a.x == b.x && a.y == b.y;
}

Point2D getKeyFirstRow(const int indexInRow) {
    return Point2D(85 + indexInRow * 38, 140);
}
Point2D getKeySecondRow(const int indexInRow) {
    return Point2D(95 + indexInRow * 38 + (indexInRow > 5 ? 1 : 0),
                   179);
}
Point2D getKeyThirdRow(const int indexInRow) {
    return Point2D(122 + indexInRow * 38 + (indexInRow > 3 ? 1 : 0),
                   219);
}

Point2D Keyboard::getKeyByIndex(const int index) const {
    return (index < 10) ? getKeyFirstRow(index)
                        : (index < 19) ? getKeySecondRow(index - 10)
                                       : getKeyThirdRow(index - 19);
}

int Keyboard::getKeyIndex(const char key) const {
    for (int i = 0; i < sizeof(configuration.mapping); i++)
        if (configuration.mapping[i] == key) return i;
    return -1;
}

Point2D Keyboard::getPosition(char key) const {
    const int index = getKeyIndex(key);
    return getKeyByIndex(index);

}

Keyboard::Keyboard(const Configuration mapping)
    : configuration(mapping) {}


Configuration::Configuration(const char * str) {
    memcpy(mapping, str, sizeof(mapping));
}
Configuration::Configuration(const Configuration & conf, uint32_t mutation) {
    memcpy(mapping, conf.mapping, sizeof(mapping));
    uint32_t i = mutation % 26;
    uint32_t j = (mutation >> 8) % 26;
    char a = mapping[i];
    mapping[i] = mapping[j];
    mapping[j] = a;
}

int Keyboard::getFirstKeyIndex(const char *input,
                               const int len) const {
    return len > 0 ? getKeyIndex(input[0]) : -1;
}

class InitializeCachedDistance {
  public:
    InitializeCachedDistance() {
        Keyboard keyboard(
            Configuration("qwertyuiopasdfghjklzxcvbnm"));
        for (int i = 0; i < 26; i++) {
            dist[i][i] = 0;
            for (int j = i + 1; j < 26; j++) {
                Point2D p1 = keyboard.getKeyByIndex(i);
                Point2D p2 = keyboard.getKeyByIndex(j);
                const int val =
                    roundf(sqrtf((p1.x - p2.x) * (p1.x - p2.x) +
                                 (p1.y - p2.y) * (p1.y - p2.y)));
                dist[i][j] = dist[j][i] = val;
            }
        }
        for (int i = 0; i < 26; i++) {
            left[i] = 0;
            sameX[i] = 0;
            for (int j = 0; j < 26; j++){
                if (isLeft(keyboard, i, j)) left[i] |= (1 << j);
                if (isSameX(keyboard, i, j)) sameX[i] |= (1 << j);
            }
        }
    }
    bool isLeft(Keyboard &keyboard, const int i, const int j) const {
        Point2D firstPos = keyboard.getKeyByIndex(i);
        Point2D secondPos = keyboard.getKeyByIndex(j);
        return firstPos.x < secondPos.x;
    }

    bool isSameX(Keyboard &keyboard, const int i, const int j) const {
        Point2D firstPos = keyboard.getKeyByIndex(i);
        Point2D secondPos = keyboard.getKeyByIndex(j);
        return firstPos.x == secondPos.x;
    }

    int dist[26][26];
    int left[26];
    int sameX[26];
} cached;

int Keyboard::getSecondKeyIndex(const char *input,
                                const int len,
                                const int firstKey) const {
    for (int i = 1; i < len; i++)
        if (input[i] != input[0]) {
            const int candidate = getKeyIndex(input[i]);
            if ((cached.sameX[firstKey] & (1 << candidate)) == 0)
                return candidate;
        }
    return -1;
}



Fingers Keyboard::initPosition(const char *input,
                               const int len) const {
    const int firstKey = getFirstKeyIndex(input, len);
    const int secondKey = getSecondKeyIndex(input, len, firstKey);
    Fingers res;
    if (secondKey == -1) {
        const bool firstKeyIsMostRight =
            firstKey != 9 && firstKey != 18 && firstKey != 25;
        res.right = firstKeyIsMostRight ? firstKey + 1 : firstKey;
        res.left  = firstKeyIsMostRight ? firstKey : firstKey - 1;
    } else {
        const bool rightFirst = isLeft(secondKey, firstKey);
        res.right = rightFirst ? firstKey : secondKey;
        res.left = rightFirst ? secondKey : firstKey;
    }
    return res;
}


bool Keyboard::isLeft(const int key1, const int key2) const {
    return (cached.left[key1] & (1 << key2)) != 0;
}
int Keyboard::dist(const int key1, const int key2) const {
    return cached.dist[key1][key2];
}

int Keyboard::distance(const char *input, const int len,
                       const Fingers &initFingers) const {
    Fingers fingers = initFingers;
    int distance = 0;
    for (int i = 0; i < len; i++) {
        const int dest = getKeyIndex(input[i]);
        const int distanceLeft = dist(fingers.left, dest);
        const int distanceRight = dist(fingers.right, dest);
        const bool canUseLeftFinger = isLeft(dest, fingers.right);
        const bool canUseRightFinger = isLeft(fingers.left, dest);
        const bool useLeft = !canUseRightFinger ||
            (distanceLeft <= distanceRight && canUseLeftFinger);

        distance += useLeft ? distanceLeft : distanceRight;
        (useLeft ? fingers.left : fingers.right) = dest;
    }

    return distance;
}

Solution::Solution(const Solution &sol, uint32_t mutation)
    : Solution(
          Configuration(sol.keyboard.getConfiguration(), mutation),
          sol.input, sol.len) {}

Solution &Solution::operator=(const Solution &sol) { 
    keyboard = sol.keyboard;
    fingers = sol.fingers;
    dist = sol.dist;

    return *this; 
}
const auto t_start = std::chrono::high_resolution_clock::now();
const std::clock_t c_start = std::clock();

bool inTime(std::clock_t c_start, const double timelimit) {
    auto t_end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double, std::milli>(
        t_end - t_start).count();
    return duration < timelimit * 1000;
}

std::string readInput() {
    std::ifstream fin("keyboard.in");
    std::string s;
    std::getline(fin, s);
    std::getline(fin, s);
    return s;
}

void write(const Solution &solution) {
    std::ofstream fout("keyboard.out");
    auto &conf = solution.keyboard.getConfiguration().mapping;
    for (int i = 0; i < sizeof(conf); i++) fout << conf[i];
    fout << std::endl;
    fout << solution.fingers.left + 1 << " "
         << solution.fingers.right + 1 << std::endl;
}

Solution * best = nullptr;

void findBetterSolution(uint32_t seed) {
    auto rnd = std::minstd_rand(seed);

    Solution *myBest = new Solution(*best, 1234);

    while (inTime(c_start, 2.8)) {

        if (best->dist < myBest->dist) {
            if (best->dist < myBest->dist) *myBest = *best;
        }

        for (int i = 0; i < 256; i++) {
            Solution sol(*myBest, rnd());
            if (myBest->dist > sol.dist) *myBest = sol;
        }

        if (best->dist > myBest->dist) *best = *myBest;
        
    }

    delete myBest;
}

int main(int argc, char *argv[]) {

    const std::string text = readInput();

    best = new Solution(Configuration("iutdjncorepbmyagshkwlxzqvf"),
                  text.c_str(), strlen(text.c_str()));

    findBetterSolution( 1234);


    write(*best);
    delete best;
    return EXIT_SUCCESS;
}
