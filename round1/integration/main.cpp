#include "keyboard.h"
#include "answer.h"
#include "simulated_annealing.h"
#include "progress.h"

int main(int argc, char *argv[]) {
    Problem p(fopen("keyboard.in", "r"));
    Progress progress(2.8);
    SimulatedAnnealing sa(p, progress);
    Answer best = sa.optimize(1234);
    best.write(fopen("keyboard.out", "w"), p);
    progress.report(stdout);
    return EXIT_SUCCESS;
}
