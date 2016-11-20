#include "keyboard.h"
#include "answer.h"

Answer::Answer(std::minstd_rand &generator, const Problem &problem)
    : Answer(Keyboard("iutdjncorepbmyagshkwlxzqvf"), problem) {
    for (int i = 0; i < 26; i++)
        keyboard.swapKeys(i, generator() % 26);
    dist = keyboard.distance(problem);
}

void Answer::write(FILE *file, const Problem &problem) {
    Fingers fingers = keyboard.initPosition(problem);
    fprintf(file, "%d %d\n", fingers.left+1, fingers.right+1);
    char mapping[32];
    keyboard.getMapping(mapping);
    mapping[26] = '\0';
    fprintf(file, "%s\n", mapping);
}
