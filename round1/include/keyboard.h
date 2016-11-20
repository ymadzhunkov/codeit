#pragma once
#include "problem.h"
#include <cstdint>

struct Point2D {
    explicit Point2D(const unsigned int x, const unsigned int y);
    unsigned int x;
    unsigned int y;
    friend bool operator==(const Point2D &a, const Point2D &b);
};


struct Fingers {
    int left, right;
};

Point2D getKeyByIndex(const int index);
int dist(const int key1, const int key2);

class Keyboard {
public:
    Keyboard(const char * map);
    int     distance(const Problem &problem) const;
    int     getKeyIndex(const char key) const;
    int     getFirstKeyIndex(const Problem & problem) const;
    int     getSecondKeyIndex(const Problem &problem,
                          const int firstKey) const;
    Fingers initPosition(const Problem & problem) const;

    void    swapKeys(const int i, const int j);
    void    getMapping(char * map) const;
private:
    char mapping[26];
};

