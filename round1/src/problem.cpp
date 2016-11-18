#include "problem.h"

Problem::Problem(FILE *file) : input(nullptr), size(0) {
    fscanf(file, "%d", &size);
    input.reset(new char[size + 1]);
    fscanf(file, "%s", input.get());
}

Problem::Problem(std::minstd_rand &generator, const int length)
    : input(new char[length + 1]), size(length) {
    for (int i = 0; i < length; i++)
        input[i] = 'a' + (generator() % 26);
    input[length] = '\0';
}

Problem::Problem(const char *inputStr, const int length)
    : input(new char[length]), size(length) {
    for (int i = 0; i < length; i++) input[i] = inputStr[i];
}

const char *Problem::getInput() const { return input.get(); }

int Problem::getSize() const { return size; }
