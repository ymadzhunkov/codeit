#pragma once
#include <random>
#include "answer.h"
class Problem;
class Progress;
class ProgressMetrics;
struct ReverseTransition;

// TODO 
// 1. Implement parrallel SA with shared state
// 2. Implement parrallel SA with state per thread
// 3. Implement cooling shedule as parameters

class SimulatedAnnealing {
  public:
    SimulatedAnnealing(const Problem &problem,
                       const Progress &progress);
    ~SimulatedAnnealing();

    void optimize(const uint32_t seed) const;

    const Answer & getBest() const;
    void updateBest(Answer &state, ProgressMetrics &metrics) const;


    bool keepTransition(Answer &state, ProgressMetrics &metrics,
                        std::minstd_rand &generator) const;
    float getTemperature(const ProgressMetrics &metrics) const;


    ReverseTransition &&transition(Answer &state,
                                   std::minstd_rand &generator) const;
    void reverse(Answer &state, const ReverseTransition rev) const;
    Answer &&initState(std::minstd_rand &generator) const;

    void setAlgorithmParameters(const float * params);

  private:
    void setInitParams();
    const Problem &problem;
    const Progress &progress;
    mutable Answer best;
    float params    [3];
};
