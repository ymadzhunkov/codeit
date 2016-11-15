#include "problem.h"

Problem::Problem(FILE *file) : input(nullptr), size(0) {
    fscanf(file, "%d", &size);
    input.reset(new char[size + 1]);
    fscanf(file, "%s", input.get());
}

