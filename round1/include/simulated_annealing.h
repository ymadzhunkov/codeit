#pragma once
#include <random>
#include "answer.h"
class Problem;
class Progress;
class ProgressMetrics;
struct ReverseTransition;

class SimulatedAnnealing {
  public:
    SimulatedAnnealing(const Problem &problem,
                       const Progress &progress);
    ~SimulatedAnnealing();

    void optimize(const uint32_t seed) const;

    bool keepTransition(Answer &state, ProgressMetrics &metrics,
                          std::minstd_rand &generator) const;

    float getTemperature(const ProgressMetrics & metrics) const;

    ReverseTransition &&transition(Answer &state,
                                   std::minstd_rand &generator,
                                   const Problem &problem) const;

    void reverse(Answer &state, const ReverseTransition rev) const;

    void updateBest(Answer &state, ProgressMetrics &metrics) const;

    const Answer & getBest() const { return best; }

    Answer && initState(std::minstd_rand &generator) const;
  private:
    const Problem  & problem;
    const Progress & progress;
    mutable Answer best;
};
