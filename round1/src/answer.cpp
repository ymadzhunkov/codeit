#include "keyboard.h"
#include "answer.h"

Answer::Answer(const Problem &problem)
    : Answer(Keyboard("iutdjncorepbmyagshkwlxzqvf"), problem) {}

void Answer::write(FILE *file, const Problem &problem) const {
    Fingers fingers = keyboard.initPosition(problem);
    fprintf(file, "%d %d\n", fingers.left + 1, fingers.right + 1);
    char mapping[32];
    keyboard.getMapping(mapping);
    mapping[26] = '\0';
    fprintf(file, "%s\n", mapping);
}
