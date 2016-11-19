#pragma once
#include <random>
#include "keyboard.h"

class Answer {
  public:
    Answer(std::minstd_rand &generator, const Problem &problem);

    Answer(const Keyboard keyboard, const Problem &problem)
        : keyboard(keyboard), dist(keyboard.distance(problem)) {}

    Answer(std::minstd_rand &generator, const Answer &sol,
             const Problem &problem);

    void write(FILE * file, const Problem &problem);

    Keyboard keyboard;
    int dist;
    int getFitness() const { return dist; }
};
