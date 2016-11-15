#pragma once
#include <memory>

class Problem {
  public:
    Problem(const char *inputStr, const int length)
        : input(new char[length]), size(length) {
        for (int i = 0; i < length; i++) input[i] = inputStr[i];
    }

    Problem(FILE * file);
    const char *getInput() const { return input.get(); }
    int getSize() const { return size; }

  private:
    std::unique_ptr<char[]> input;
    int size;
};
