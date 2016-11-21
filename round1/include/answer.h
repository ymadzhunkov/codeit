#pragma once
#include <random>
#include "keyboard.h"

class Answer {
  public:
    Answer(const Problem &problem);

    Answer(const Keyboard keyboard, const Problem &problem)
        : keyboard(keyboard), dist(keyboard.distance(problem)) {}

    void write(FILE * file, const Problem &problem) const;

    Keyboard keyboard;
    int dist;
};
