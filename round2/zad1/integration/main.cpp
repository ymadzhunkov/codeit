#include "problem.h"
#include "answer.h"
#include <cstdlib>

int main(int argc, char *argv[]) {
    Problem problem(fopen("keyboard.in", "r"));
    Answer best = solve(problem);
    best.write(fopen("keyboard.out", "w"), problem);
    return EXIT_SUCCESS;
}
