#include "progress.h"
#include <stdio.h>

Progress::Progress(const float timelimit)
    : t_start(std::chrono::high_resolution_clock::now()),
      c_start(std::clock()), rtimelimit(1.0f / timelimit) {}

float Progress::getCPUTime() const {
    std::clock_t c_end = std::clock();
    return (c_end - c_start) * (1.0f / CLOCKS_PER_SEC);
}

float Progress::getRealTime() const {
    auto t_end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float>(t_end - t_start).count();
}

float Progress::update(const ProgressMetrics & metrics) const {
    this->metrics = metrics;
    float progress = getRealTime() * rtimelimit;
//    printf("%.2f %.0f %.0f\n", progress, metrics.currentState,
//           metrics.currentBest);
    return progress; 
}

ProgressMetrics::ProgressMetrics()
    : numIterations(0), numTransitions(0), numBestUpdates(0),
      currentBest(0.0f), currentState(0.0f) {}


void Progress::report(FILE *file) const {
    const float real = getRealTime();
    const float user = getCPUTime();

    fprintf(file, "number of candidates  = %d\n",
            metrics.numIterations);
    fprintf(file, "number of transitions = %d\n",
            metrics.numTransitions);
    fprintf(file, "number of best update = %d\n",
            metrics.numBestUpdates);
    fprintf(file, "computation speed     = %.2f MIter/s\n",
            metrics.numIterations / (1.0e6f * real));
    fprintf(file, "best fitness reached  = %.0f\n",
            metrics.currentBest);
    fprintf(file, "CPU time              = %.2f sec\n", user);
    fprintf(file, "Real time             = %.2f sec\n", real);
}
