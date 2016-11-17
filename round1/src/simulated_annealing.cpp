#include "simulated_annealing.h"
#include "problem.h"
#include "solution.h"

SimulatedAnnealing::SimulatedAnnealing(const Problem &problem,
                                       const float timelimit)
    : t_start(std::chrono::high_resolution_clock::now()),
      c_start(std::clock()), timelimit(timelimit), problem(problem) {
}

SimulatedAnnealing::~SimulatedAnnealing(){}

Answer &&SimulatedAnnealing::optimize(const uint32_t seed) const {
    auto rnd = std::minstd_rand(seed);
    Answer state(rnd, problem);
    Answer best = state;
    size_t iter = 0;
    for (; terminationCreiteria(iter); iter++) {
        Answer candidate(rnd, state, problem);

        if (best.getFitness() > candidate.getFitness())
            best = candidate;

        const float temp = getTemperature(iter);
        if (shouldMove(state.getFitness(), candidate.getFitness(),
                       temp, rnd))
            state = candidate;
    }

    // update stats
    stats.problemSize = problem.getSize();
    stats.performedIterations = iter;
    stats.usedSeed = seed;

    stats.CPUTimeInSeconds = getCPUTime();
    stats.RealTimeInSeconds = getRealTime();
    stats.bestAnswer = best.getFitness();
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

float SimulatedAnnealing::getCPUTime() const {
    std::clock_t c_end = std::clock();
    return (c_end - c_start) * (1.0f / CLOCKS_PER_SEC);
}

float SimulatedAnnealing::getRealTime() const {
    auto t_end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float>(t_end - t_start).count();
}

bool SimulatedAnnealing::inTime() const {
    return getRealTime() < timelimit;
}

bool SimulatedAnnealing::terminationCreiteria(const size_t iteration)
    const {
    if ((iteration & 127) == 0)
        return inTime();
    else 
        return true;
}

float
SimulatedAnnealing::getTemperature(const size_t iteration) const {
    return 20.0 * (1.0 + 20.0/(iteration*iteration));
}

void reportStats(FILE * file, const Statistics & stats) {
    fprintf(file, "performed iterations = %d\n",
            stats.performedIterations);
    fprintf(file, "computation speed    = %.2f iter/s\n",
            stats.performedIterations / stats.RealTimeInSeconds);
    fprintf(file, "best fitness reached = %.0f\n",
            stats.bestAnswer);
    fprintf(file, "CPU time             = %.2f sec\n",
            stats.CPUTimeInSeconds);
    fprintf(file, "Real time            = %.2f sec\n",
            stats.RealTimeInSeconds);

//    fprintf(file, "computation speed = %.2f iter/ms\n");
//    fprintf(file, "computation speed = %.2f iter/ms\n");
    
/*    std::cout << totalIter / duration << " iter/ms\n"
              << "CPU time used: " << 1000.0 * (c_end - c_start) /
                                          CLOCKS_PER_SEC << " ms\n"
              << "Wall clock time passed: " << duration << " ms\n"
              << "Distance = " << best->dist << "\n";
*/
}

