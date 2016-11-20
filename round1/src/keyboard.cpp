#include "keyboard.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

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

Point2D getKeyByIndex(const int index) {
    return (index < 10) ? getKeyFirstRow(index)
                        : (index < 19) ? getKeySecondRow(index - 10)
                                       : getKeyThirdRow(index - 19);
}

int Keyboard::getKeyIndex(const char key) const {
    return mapping[key - 'a'];
}

Keyboard::Keyboard(const char *str) {
    for (int i = 0; i < sizeof(mapping); i++)
        mapping[str[i] - 'a'] = i;
}

void Keyboard::swapKeys(const int i, const int j) {
    char a = mapping[i];
    mapping[i] = mapping[j];
    mapping[j] = a;
}

int Keyboard::getFirstKeyIndex(const Problem & problem) const {
    return problem.getSize() > 0 ? getKeyIndex(problem.getInput()[0])
                                : -1;
}

class InitializeCachedDistance {
  public:
    InitializeCachedDistance() {
        for (int i = 0; i < 26; i++) {
            dist[i][i] = 0;
            for (int j = i + 1; j < 26; j++) {
                Point2D p1 = getKeyByIndex(i);
                Point2D p2 = getKeyByIndex(j);
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
                if (isLeft(i, j)) left[i] |= (1 << j);
                if (isSameX(i, j)) sameX[i] |= (1 << j);
            }
        }
    }
private:
    bool isLeft(const int i, const int j) const {
        Point2D firstPos = getKeyByIndex(i);
        Point2D secondPos = getKeyByIndex(j);
        return firstPos.x < secondPos.x;
    }

    bool isSameX(const int i, const int j) const {
        Point2D firstPos = getKeyByIndex(i);
        Point2D secondPos = getKeyByIndex(j);
        return firstPos.x == secondPos.x;
    }
public:
    int dist[26][26];
    int left[26];
    int sameX[26];
} cached;


bool isLeft(const int key1, const int key2) {
    return (cached.left[key1] & (1 << key2)) != 0;
}

int dist(const int key1, const int key2) {
    return cached.dist[key1][key2];
}

int Keyboard::getSecondKeyIndex(const Problem &problem,
                                const int firstKey) const {
    const char *input = problem.getInput();
    for (int i = 1; i < problem.getSize(); i++)
        if (input[i] != input[0]) {
            const int candidate = getKeyIndex(input[i]);
            if ((cached.sameX[firstKey] & (1 << candidate)) == 0)
                return candidate;
        }
    return -1;
}

Fingers Keyboard::initPosition(const Problem & problem) const {
    const int firstKey = getFirstKeyIndex(problem);
    const int secondKey = getSecondKeyIndex(problem, firstKey);
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



int Keyboard::distance(const Problem & problem) const {
    Fingers fingers = initPosition(problem);
    int distance = 0;
    for (int i = 0; i < problem.getSize(); i++) {
        const int dest = getKeyIndex(problem.getInput()[i]);
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

void Keyboard::getMapping(char *map) const {
    for (char c = 'a'; c <= 'z'; c++) map[getKeyIndex(c)] = c;
}
