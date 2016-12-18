#include "answer.h"

Answer::Answer(const int m, const int x[])
    : rightHandIndex(m), x(x) {}

void Answer::write(FILE *file, const int numParameters) const {
    fprintf(file, "%d\n", rightHandIndex + 1);
    for (int i = 0; i < numParameters; i++)
        fprintf(file, "%d ", x[i]);
    fprintf(file, "\n");
    fclose(file);
}
