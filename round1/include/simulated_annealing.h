#pragma once
#include <chrono>
#include <random>

class Answer;
class Problem;


class Statistics {
public:
    int   problemSize;
    int   performedIterations;
    int   usedSeed;

    float CPUTimeInSeconds;
    float RealTimeInSeconds;
    float bestAnswer;
};
void reportStats(FILE *file, const Statistics &stats);

class SimulatedAnnealing {
  public:
    SimulatedAnnealing(const Problem &problem, const float timelimit);
    ~SimulatedAnnealing();

    Answer && optimize(const uint32_t seed) const;

    bool shouldMove(const float fitness, const float newFitness,
                    const float temp,
                    std::minstd_rand &generator) const;

    bool inTime() const;
    float getTemperature(const size_t iteration) const;
    bool terminationCreiteria(const size_t iteration) const;
    const Statistics &getStatistics() const { return stats; }

    float getCPUTime() const;
    float getRealTime() const;
  private:
    const std::clock_t c_start;
    const std::chrono::time_point<std::chrono::high_resolution_clock>
    t_start;
    const float timelimit;
    const Problem & problem;
    mutable Statistics stats;
};
