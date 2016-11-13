#pragma once
#include <string>
class Problem {
  public:
    Problem(const char *input, const int len)
        : input(input), len(len) {}
    const char *getInput() const { return input; }
    int getLen() const { return len; }

  private:
    const char *input;
    int len;
};

std::string readInput();
