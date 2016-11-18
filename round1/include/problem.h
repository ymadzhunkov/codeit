#pragma once
#include <memory>
#include <random>

class Problem {
  public:
    Problem(FILE * file);
    Problem(const char *inputStr, const int length);
    Problem(std::minstd_rand &generator, const int length);

    const char *getInput() const;
    int         getSize () const;

  private:
    std::unique_ptr<char[]> input;
    int size;
};
