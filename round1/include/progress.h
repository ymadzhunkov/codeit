#include <chrono>
#include <stdio.h>

struct ProgressMetrics {
    ProgressMetrics();
    unsigned int numIterations;
    unsigned int numTransitions;
    unsigned int numBestUpdates;
    float        currentBest;
    float        currentState;
};


class Progress {
public:
    Progress(const float timelimit);
    float update(const ProgressMetrics & metrics) const;
    float getCPUTime() const;
    float getRealTime() const;
    void report(FILE *file) const;
private:
    const std::clock_t c_start;
    const std::chrono::time_point<std::chrono::high_resolution_clock>
    t_start;
    const float rtimelimit;
    mutable ProgressMetrics metrics;
};
