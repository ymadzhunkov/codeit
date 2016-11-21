#include "keyboard.h"
#include "answer.h"
#include "simulated_annealing.h"
#include "progress.h"

int main(int argc, char *argv[]) {
    Problem problem(fopen("keyboard.in", "r"));
    Progress progress(2.8);
    SimulatedAnnealing sa(problem, progress);
    sa.optimize(1234);
    sa.getBest().write(fopen("keyboard.out", "w"), problem);
    progress.report(stdout);
    return EXIT_SUCCESS;
}
