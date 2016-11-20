#include <stdio.h>
class Problem;
class Answer {
public:
    Answer();
    void write(FILE * outfile, Problem & problem);
};
Answer solve(const Problem & problem);
