#pragma once
#include <random>
#include "keyboard.h"

class Answer {
  public:
    Answer(std::minstd_rand &generator, const Problem &problem);

    Answer(const Configuration configuration,
             const Problem &problem)
        : keyboard(configuration),
          fingers(keyboard.initPosition(problem)),
          dist(keyboard.distance(problem, fingers)) {}

    Answer(std::minstd_rand &generator, const Answer &sol,
             const Problem &problem);

    void write(FILE * file);

    Keyboard keyboard;
    Fingers fingers;
    int dist;
    int getFitness() const { return dist; }
};
