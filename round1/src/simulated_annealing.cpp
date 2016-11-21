#include "simulated_annealing.h"
#include "problem.h"
#include "answer.h"
#include "progress.h"

SimulatedAnnealing::SimulatedAnnealing(const Problem &problem,
                                       const Progress &progress)
    : problem(problem), progress(progress), best(problem) {}

SimulatedAnnealing::~SimulatedAnnealing(){}

struct ReverseTransition {
    int i, j;
};

ReverseTransition &&
SimulatedAnnealing::transition(Answer &state,
                               std::minstd_rand &generator,
                               const Problem &problem) const {
    ReverseTransition res;
    const uint32_t mutation = generator();
    res.i = mutation % 26;
    res.j = (mutation >> 8) % 26;
    state.keyboard.swapKeys(res.i, res.j);
    return std::move(res);
}

void SimulatedAnnealing::reverse(Answer &state,
                                 const ReverseTransition rev) const {
    state.keyboard.swapKeys(rev.i, rev.j);
}

void SimulatedAnnealing::keep(Answer &state,
                              ProgressMetrics &metrics) const {
    metrics.numTransitions++;
    if (best.dist > state.dist) {
        best = state;
        metrics.numBestUpdates++;
    }
}


void SimulatedAnnealing::optimize(const uint32_t seed) const {
    std::minstd_rand rnd(seed);

    Answer state(problem);
    for (int i = 0; i < 26; i++)
        state.keyboard.swapKeys(i, rnd() % 26);
    state.dist = state.keyboard.distance(problem);

    ProgressMetrics metrics;

    while (progress.update(metrics) < 1.0f) {
        const float temp = getTemperature(metrics);
        const unsigned int chunk = 512;
        for (unsigned int k = 0; k < chunk; k++) {
            ReverseTransition rev = transition(state, rnd, problem);
            const int newDist = state.keyboard.distance(problem);

            if (shouldReverseTransition(state.dist, newDist, temp,
                                        rnd)) {
                reverse(state, rev);
            } else {
                state.dist = newDist;
                keep(state, metrics);
            }

        }
        metrics.currentState = state.dist;
        metrics.currentBest  = best.dist;
        metrics.numIterations += chunk;
    }
}

bool SimulatedAnnealing::shouldReverseTransition(
    const float fitness, const float newFitness, const float temp,
    std::minstd_rand &generator) const {
    std::uniform_real_distribution<float> uniform(0.0, 1.0);
    int exp;
    frexpf(uniform(generator), &exp);
    return fitness - newFitness < exp * temp;
}

float SimulatedAnnealing::getTemperature(
    const ProgressMetrics &metrics) const {
    return log2f(3.14) * 20.0 * (1.0 + 20.0 / (metrics.numIterations *
                                 metrics.numIterations));
}

