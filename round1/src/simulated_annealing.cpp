#include "simulated_annealing.h"
#include "problem.h"
#include "answer.h"
#include "progress.h"

SimulatedAnnealing::SimulatedAnnealing(const Problem &problem,
                                       const Progress &progress)
    : problem(problem), progress(progress), best(problem) {
    setInitParams();
}

SimulatedAnnealing::~SimulatedAnnealing() {}

struct ReverseTransition {
    char i, j;
};

ReverseTransition &&
SimulatedAnnealing::transition(Answer &state,
                               std::minstd_rand &generator) const {
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

void SimulatedAnnealing::updateBest(Answer &state,
                                    ProgressMetrics &metrics) const {
    if (best.dist > state.dist) {
        best = state;
        metrics.numBestUpdates++;
    }
}

Answer &&SimulatedAnnealing::initState(std::minstd_rand &rnd) const {
    Answer state(problem);
    for (int i = 0; i < 26; i++) transition(state, rnd);
    state.dist = state.keyboard.distance(problem);
    return std::move(state);
}

void SimulatedAnnealing::optimize(const uint32_t seed) const {
    std::minstd_rand rnd(seed);
    Answer state = initState(rnd);
    ProgressMetrics metrics;
    const unsigned int chunk = 512;

    while (progress.update(metrics) < 1.0f) {
        for (unsigned int k = 0; k < chunk; k++) {
            ReverseTransition rev = transition(state, rnd);
            if (!keepTransition(state, metrics, rnd))
                reverse(state, rev);
        }
        metrics.currentState = state.dist;
        metrics.currentBest = best.dist;
        metrics.numIterations += chunk;
    }
}

const Answer &SimulatedAnnealing::getBest() const { return best; }

bool SimulatedAnnealing::keepTransition(
    Answer &state, ProgressMetrics &metrics,
    std::minstd_rand &generator) const {

    std::uniform_real_distribution<float> uniform(0.0, 1.0);
    int exp;
    frexpf(uniform(generator), &exp);

    const float temp = getTemperature(metrics);
    const int newFitness = state.keyboard.distance(problem);
    const bool keepTrans = state.dist - newFitness >= exp * temp;

    if (keepTrans) {
        state.dist = newFitness;
        metrics.numTransitions++;
        updateBest(state, metrics);
    }
    return keepTrans;
}

void SimulatedAnnealing::setInitParams() {
    params[0] = 22.0f; 
    params[1] = 20.0f;
    params[2] = 1.1f;
}
void SimulatedAnnealing::setAlgorithmParameters(const float * newParams) {
    params[0] = newParams[0];
    params[1] = newParams[1];
    params[2] = newParams[2];
}

float SimulatedAnnealing::getTemperature(
    const ProgressMetrics &metrics) const {
    const float evolution = metrics.numIterations * 1e-5f;
    return params[0] + params[1] * cosf(params[2] * evolution);
//        (cosf(metrics.numIterations * 1e-5f) + 1.1f) * 20.0f;
}

