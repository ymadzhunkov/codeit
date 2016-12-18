#include "problem.h"

Problem::Problem(FILE *file) : numEquations(0), numParameters(0) {
    bool success =
        2 == fscanf(file, "%d %d", &numEquations, &numParameters);
    rewards = new Reward[numEquations];
    equations = new int[numEquations * numParameters];
    for (int equation = 0; equation < numEquations; equation++) {
        for (int p = 0; p < numParameters; p++)
            success &=
                1 == fscanf(file, "%d",
                            &equations[equation * numParameters + p]);
        success &=
            2 == fscanf(file, "%d %d", &(rewards[equation].exact),
                        &(rewards[equation].approx));
    }
    success =
        1 == fscanf(file, "%d", &numRightSides);
    rightSides = new int[numRightSides * numEquations];
    for (int i = 0; i < numRightSides; i++)
        for (int equation = 0; equation < numEquations; equation++)
            success &=
                1 == fscanf(file, "%d",
                            &rightSides[i * numEquations + equation]);
}

Problem::~Problem() {
    delete[] rewards;
    rewards = nullptr;
    delete[] equations;
    equations = nullptr;
}

