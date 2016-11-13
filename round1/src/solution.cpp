#include "keyboard.h"
#include "solution.h"
#include <fstream>
#include <iostream>

Solution::Solution(std::minstd_rand &generator, const Solution &sol,
                   const Problem &problem)
    : Solution(
          Configuration(sol.keyboard.getConfiguration(), generator()),
          problem) {}

Solution::Solution(std::minstd_rand &generator,
                   const Problem &problem)
    : Solution(Configuration("iutdjncorepbmyagshkwlxzqvf"), problem) {
}

void write(const Solution &solution) {
    std::ofstream fout("keyboard.out");
    fout << solution.fingers.left + 1 << " "
         << solution.fingers.right + 1 << std::endl;
    auto &conf = solution.keyboard.getConfiguration().mapping;
    for (int i = 0; i < sizeof(conf); i++) fout << conf[i];
    fout << std::endl;
}
