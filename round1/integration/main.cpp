#include "keyboard.h"
#include "answer.h"
#include "simulated_annealing.h"

int main(int argc, char *argv[]) {
    Problem p(fopen("keyboard.in", "r"));
    SimulatedAnnealing sa(p, 2.8);
    Answer best = sa.optimize(1234);
    best.write(fopen("keyboard.out", "w"));
    reportStats(stdout, sa.getStatistics());
    return EXIT_SUCCESS;
}
