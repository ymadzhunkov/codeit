#include <cstdint>

struct Point2D {
    explicit Point2D(const unsigned int x, const unsigned int y);
    unsigned int x;
    unsigned int y;
    friend bool operator==(const Point2D &a, const Point2D &b);
};

struct Configuration {
    Configuration(const char * str);
    char mapping[26];
    Configuration(const Configuration & conf, uint32_t mutation);
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
    int     getKeyIndex(const char key) const;
    int     getFirstKeyIndex(const char *input, const int len) const;
    int     getSecondKeyIndex(const char * input, const int len,
                             const int firstKey) const;
    Point2D getKeyByIndex(const int index) const;
    Fingers initPosition(const char * input, const int len) const;
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

    Solution(const Solution & sol, uint32_t mutation);
    Solution &operator=(const Solution &sol);
    Keyboard keyboard;
    Fingers fingers;
    const char *input;
    const int len;
    int dist;
};