#pragma once
#include "problem.h"
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

Point2D getKeyByIndex(const int index);

class Keyboard {
public:
    Keyboard(const Configuration mapping);
    int distance(const Problem &problem,
                 const Fingers &fingers) const;
    int     getKeyIndex(const char key) const;
    int     getFirstKeyIndex(const Problem & problem) const;
    int     getSecondKeyIndex(const Problem &problem,
                          const int firstKey) const;
    Fingers initPosition(const Problem & problem) const;
    bool isLeft(const int key1, const int key2) const;
    int dist(const int key1, const int key2) const;
    const Configuration &getConfiguration() const {
        return configuration;
    }

private:
    Configuration configuration; 
};

