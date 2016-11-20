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
            const uint32_t mutation = rnd();
            const uint32_t i =  mutation % 26;
            const uint32_t j = (mutation >> 8) % 26;

            state.keyboard.swapKeys(i, j);
            const int newDist = state.keyboard.distance(problem);

            if (!shouldMove(state.dist, newDist, temp, rnd)) {
                state.keyboard.swapKeys(i, j);
            } else {
                metrics.numTransitions++;
                state.dist = newDist;
                if (best.dist > state.dist) {
                    best = state;
                    metrics.numBestUpdates++;
                }
            }

        }
        metrics.currentState = state.dist;
        metrics.currentBest  = best.dist;
        metrics.numIterations += chunk;
    }
    return std::move(best);
}

bool SimulatedAnnealing::shouldMove(
    const float fitness, const float newFitness, const float temp,
    std::minstd_rand &generator) const {
    std::uniform_real_distribution<float> uniform(0.0, 1.0);
    int exp;
    frexpf(uniform(generator), &exp);
    return fitness - newFitness > exp * temp;
}

float SimulatedAnnealing::getTemperature(
    const ProgressMetrics &metrics) const {
    return log2f(3.14) * 20.0 * (1.0 + 20.0 / (metrics.numIterations *
                                 metrics.numIterations));
}

