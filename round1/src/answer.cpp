#include "keyboard.h"
#include "answer.h"

Answer::Answer(std::minstd_rand &generator, const Problem &problem)
    : Answer(Keyboard("iutdjncorepbmyagshkwlxzqvf"), problem) {
    for (int i = 0; i < 20; i++) 
        keyboard.mutate(generator());
}

void Answer::write(FILE *file, const Problem &problem) {
    Fingers fingers = keyboard.initPosition(problem);
    fprintf(file, "%d %d\n", fingers.left+1, fingers.right+1);
    char mapping[32];
    keyboard.getMapping(mapping);
    mapping[26] = '\0';
    fprintf(file, "%s\n", mapping);
}

void Answer::mutate(const uint32_t mutation, const Problem &problem) {
    keyboard.mutate(mutation);
    dist = keyboard.distance(problem);
}

void Answer::unmutate(const uint32_t mutation, const int prevDist) {
    keyboard.mutate(mutation);
    dist = prevDist;
}
