#include "keyboard.h"
#include "answer.h"
#include "simulated_annealing.h"
#include "progress.h"
#include "differential_evolution.h"

float evaluate(const Individual & agent) {
    std::minstd_rand generator(4433);
    const int problemSize = 120;
    int total = 0;
    for (int i = 0; i < 16; i++) {
        Problem problem(generator, problemSize);
        Progress progress(2.8);
        SimulatedAnnealing sa(problem, progress);
        sa.setAlgorithmParameters(agent.coordinates);
        sa.optimize(1234);
        total += sa.getBest().dist;
        progress.report(stdout);
    }
    return total * (1.0/16);

}


int main(int argc, char *argv[]) {
    EvelutionParams params;
    params.crossoverProbability = 0.2;
    params.differentialWeight = 1.0;
    Individual best = differentialEvolution(params, &evaluate);

    return EXIT_SUCCESS;
}
