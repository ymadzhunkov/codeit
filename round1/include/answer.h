#pragma once
#include <random>
#include "keyboard.h"

class Answer {
  public:
    Answer(std::minstd_rand &generator, const Problem &problem);

    Answer(const Keyboard keyboard, const Problem &problem)
        : keyboard(keyboard), dist(keyboard.distance(problem)) {}

    void mutate(const uint32_t mutation, const Problem &problem);

    void unmutate(const uint32_t mutation, const int prevDist);

    void write(FILE * file, const Problem &problem);

    Keyboard keyboard;
    int dist;
    int getFitness() const { return dist; }
};
