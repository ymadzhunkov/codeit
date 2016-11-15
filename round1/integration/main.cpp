#include "keyboard.h"
#include "solution.h"
#include "simulated_annealing.h"

int main(int argc, char *argv[]) {
    Problem p(fopen("keyboard.in", "r"));
    SimulatedAnnealing sa(p, 2.8);
    Solution best = sa.optimize(1234);
    best.write(fopen("keyboard.out", "w"));
    reportStats(stdout, sa.getStatistics());
    return EXIT_SUCCESS;
}
