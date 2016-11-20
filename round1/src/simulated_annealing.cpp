#include "simulated_annealing.h"
#include "problem.h"
#include "answer.h"
#include "progress.h"

SimulatedAnnealing::SimulatedAnnealing(const Problem &problem,
                                       const Progress &progress)
    : problem(problem), progress(progress) {}

SimulatedAnnealing::~SimulatedAnnealing(){}

Answer &&SimulatedAnnealing::optimize(const uint32_t seed) const {
    auto rnd = std::minstd_rand(seed);
    Answer state(rnd, problem);
    Answer best = state;
    ProgressMetrics metrics;

    while (progress.update(metrics) < 1.0f) {
        const float temp = getTemperature(metrics);
        const unsigned int chunk = 512;
        for (unsigned int k = 0; k < chunk; k++) {
            const int oldDist = state.getFitness();
            const uint32_t mutation = rnd();
            state.mutate(mutation, problem);

            if (best.getFitness() > state.getFitness()) {
                best = state;
                metrics.numBestUpdates++;
            }

            if (!shouldMove(oldDist, state.getFitness(), temp, rnd))
                state.unmutate(mutation, oldDist);
            else
                metrics.numTransitions++;
        }
        metrics.currentState = state.getFitness();
        metrics.currentBest  = best.getFitness();
        metrics.numIterations += chunk;
    }
    return std::move(best);
}

bool SimulatedAnnealing::shouldMove(
    const float fitness, const float newFitness, const float temp,
    std::minstd_rand &generator) const {
        if (newFitness < fitness) {
            return true;
        } else {
            const float distance = newFitness - fitness;
            const float prob = 1.0 - expf(-distance / temp);
            std::uniform_real_distribution<float> uniform(0.0, 1.0);
            return prob < uniform(generator); 
        }
}

float SimulatedAnnealing::getTemperature(
    const ProgressMetrics &metrics) const {
    return 20.0 * (1.0 + 20.0 / (metrics.numIterations *
                                 metrics.numIterations));
}

