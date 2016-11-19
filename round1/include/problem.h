#pragma once
#include <random>

class Problem {
  public:
    Problem(FILE * file);
    Problem(const char *inputStr, const int length);
    Problem(std::minstd_rand &generator, const int length);

    const char * getInput() const { return input; }
    int          getSize() const { return size; }

  private:
    int size;
    char input[200];
};
