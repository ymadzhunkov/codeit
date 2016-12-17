#include "problem.h"

Problem::Problem(FILE *file) : numEquations(0), numParameters(0) {
    bool success =
        2 == fscanf(file, "%d %d", &numEquations, &numParameters);
    rewards = new Reward[numEquations];

    for (int equation = 0; equation < numEquations; equation++) {
        for (int p = 0; p < numParameters; p++) {
            int f;
            success &= 1 == fscanf(file, "%d", &f);
        }
        success &=
            2 == fscanf(file, "%d %d", &(rewards[equation].exact),
                        &(rewards[equation].approx));
    }
}

Problem::~Problem() {
    delete[] rewards;
    rewards = nullptr;
}

