#include "keyboard.h"
#include "solution.h"

#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstring>
#include <random> 
#include <thread>
#include <mutex>

const auto t_start = std::chrono::high_resolution_clock::now();
const std::clock_t c_start = std::clock();

bool inTime(std::clock_t c_start, const double timelimit) {
    auto t_end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double, std::milli>(
        t_end - t_start).count();
    return duration < timelimit * 1000;
}


Solution * best = nullptr;
std::mutex solution_mutex;
size_t totalIter = 0;

void findBetterSolution(uint32_t seed, const Problem & p) {
    auto rnd = std::minstd_rand(seed);
    
    Solution * myBest = nullptr;
    {
        std::lock_guard<std::mutex> guard(solution_mutex);
        myBest = new Solution(rnd, *best, p);
    }

    size_t iter = 0;
    while (inTime(c_start, 2.8)) {

        if (best->dist < myBest->dist) {
            std::lock_guard<std::mutex> guard(solution_mutex);
            if (best->dist < myBest->dist) 
                *myBest = *best;
        }
              
        for (int i = 0; i < 256; i++) {
            Solution sol(rnd, *myBest, p);
            if (myBest->dist > sol.dist) 
                *myBest = sol;
        }
        iter += 256;

        if (best->dist > myBest->dist) {
            std::lock_guard<std::mutex> guard(solution_mutex);
            if (best->dist > myBest->dist) 
                *best = *myBest;
        }
 
    }

    delete myBest;

    {
        std::lock_guard<std::mutex> guard(solution_mutex);
        totalIter += iter;
    }
}

void outputStats() {
    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double, std::milli>(
        t_end - t_start).count();
    std::cout << totalIter / duration << " iter/ms\n"
              << "CPU time used: " << 1000.0 * (c_end - c_start) /
                                          CLOCKS_PER_SEC << " ms\n"
              << "Wall clock time passed: " << duration << " ms\n"
              << "Distance = " << best->dist << "\n";
}

int main(int argc, char *argv[]) {

    const std::string text = readInput();
    Problem p(text.c_str(), strlen(text.c_str()));
    auto rnd = std::minstd_rand(2222);
    best = new Solution(rnd, p);

    int num_threads = std::thread::hardware_concurrency();
    if (num_threads > 32) num_threads = 32;
    std::thread t[32];

    for (int i = 0; i < num_threads; ++i)
        t[i] = std::thread(findBetterSolution, 1234 + i * i * i, p);

    for (int i = 0; i < num_threads; ++i)
        t[i].join();

    outputStats();
    write(*best);
    delete best;
    return EXIT_SUCCESS;
}
