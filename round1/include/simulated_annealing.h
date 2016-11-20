#pragma once
#include <random>

class Answer;
class Problem;
class Progress;

class SimulatedAnnealing {
  public:
    SimulatedAnnealing(const Problem &problem,
                       const Progress &progress);
    ~SimulatedAnnealing();

    Answer && optimize(const uint32_t seed) const;

    bool shouldMove(const float fitness, const float newFitness,
                    const float temp,
                    std::minstd_rand &generator) const;

    float getTemperature(const size_t iteration) const;

  private:
    const Problem  & problem;
    const Progress & progress;
};
