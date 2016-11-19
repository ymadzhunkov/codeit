#include "keyboard.h"
#include "answer.h"
#include <cstring>

Answer::Answer(std::minstd_rand &generator, const Answer &sol,
               const Problem &problem)
    : keyboard(sol.keyboard, generator()),
      dist(keyboard.distance(problem)) {}

Keyboard randomConfig(std::minstd_rand &generator) {
    Keyboard res("iutdjncorepbmyagshkwlxzqvf");
    for (int i = 0; i < sizeof(res); i++) {
        uint32_t r = generator();
        res.mutate(r);
    }
    return res;
}


Answer::Answer(std::minstd_rand &generator,
                   const Problem &problem)
    : Answer(randomConfig(generator), problem) {
}

void Answer::write(FILE *file, const Problem &problem) {
    Fingers fingers = keyboard.initPosition(problem);
    fprintf(file, "%d %d\n", fingers.left+1, fingers.right+1);
    char mapping[32];
    keyboard.getMapping(mapping);
    mapping[26] = '\0';
    fprintf(file, "%s\n", mapping);
}
