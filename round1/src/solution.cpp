#include "keyboard.h"
#include "solution.h"
#include <fstream>
#include <iostream>

Solution::Solution(std::minstd_rand &generator, const Solution &sol,
                   const Problem &problem)
    : Solution(
          Configuration(sol.keyboard.getConfiguration(), generator()),
          problem) {
    
}

Configuration randomConfig(std::minstd_rand &generator) {
    Configuration res("iutdjncorepbmyagshkwlxzqvf");
    for (int i = 0; i < sizeof(res.mapping); i++) {
        uint32_t r = generator();
        int j = r % sizeof(res.mapping);
        char a = res.mapping[i];
        res.mapping[i] = res.mapping[j];
        res.mapping[j] = a;
    }
    return res;
}


Solution::Solution(std::minstd_rand &generator,
                   const Problem &problem)
    : Solution(randomConfig(generator), problem) {
}

void write(const Solution &solution) {
    std::ofstream fout("keyboard.out");
    fout << solution.fingers.left + 1 << " "
         << solution.fingers.right + 1 << std::endl;
    auto &conf = solution.keyboard.getConfiguration().mapping;
    for (int i = 0; i < sizeof(conf); i++) fout << conf[i];
    fout << std::endl;
}
