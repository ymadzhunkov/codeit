#pragma once
#include <stdio.h>
struct Reward {
    int exact;
    int approx;
};

class Problem {
  public:
    Problem(FILE * file);
    virtual ~Problem();
    int numEquations;
    int numParameters;
    int numRightSides;
    Reward * rewards;
    int    * equations;
    int    * rightSides;
};
