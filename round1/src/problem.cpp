#include "problem.h"

Problem::Problem(FILE *file) : size(0) {
    fscanf(file, "%d", &size);
    fscanf(file, "%s", input);
}

Problem::Problem(std::minstd_rand &generator, const int length)
    : size(length) {
    for (int i = 0; i < length; i++)
        input[i] = 'a' + (generator() % 26);
    input[length] = '\0';
}

Problem::Problem(const char *inputStr, const int length)
    : size(length) {
    for (int i = 0; i < length; i++) input[i] = inputStr[i];
}

