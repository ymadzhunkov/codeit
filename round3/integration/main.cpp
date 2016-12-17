#include "answer.h"
#include "problem.h"
#include <cstdlib>

int main(int argc, char *argv[]) {
    Problem problem(fopen("equations.in", "r"));
    Answer a;
    a.write(fopen("equations.out", "w"));
    return EXIT_SUCCESS;
}
