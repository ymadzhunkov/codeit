#pragma once
#include <random>
#include "keyboard.h"

class Solution {
  public:
    Solution(std::minstd_rand &generator, const Problem &problem);

    Solution(const Configuration configuration,
             const Problem &problem)
        : keyboard(configuration),
          fingers(keyboard.initPosition(problem)),
          dist(keyboard.distance(problem, fingers)) {}

    Solution(std::minstd_rand &generator, const Solution &sol,
             const Problem &problem);

    void write(FILE * file);

    Keyboard keyboard;
    Fingers fingers;
    int dist;
    int getFitness() const { return dist; }
};
