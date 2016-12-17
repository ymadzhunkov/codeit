#pragma once
#include <stdio.h>
struct Reward {
    int exact;
    int approx;
};
struct Matrix {
    
};
class Problem {
  public:
    Problem(FILE * file);
    virtual ~Problem();
    int numEquations;
    int numParameters;
    Reward * rewards;
    Matrix a;
};
