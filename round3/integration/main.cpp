#include "answer.h"
#include "problem.h"
#include <cstdlib>

int main(int argc, char *argv[]) {
    Problem problem(fopen("equations.in", "r"));
    Answer a(0, nullptr);
    a.write(fopen("equations.out", "w"), problem.numParameters);
    return EXIT_SUCCESS;
}
