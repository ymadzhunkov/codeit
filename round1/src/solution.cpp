#include "keyboard.h"
#include "solution.h"
#include <cstring>

Answer::Answer(std::minstd_rand &generator, const Answer &sol,
                   const Problem &problem)
    : Answer(
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


Answer::Answer(std::minstd_rand &generator,
                   const Problem &problem)
    : Answer(randomConfig(generator), problem) {
}

void Answer::write(FILE * file) {
    fprintf(file, "%d %d\n", fingers.left+1, fingers.right+1);
    char d[32];
    memcpy(d, keyboard.getConfiguration().mapping, 26);
    d[26] = '\0';
    fprintf(file, "%s\n", d);
}
