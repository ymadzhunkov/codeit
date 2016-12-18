#pragma once
#include <stdio.h>
class Answer {
  public:
    Answer(const int m, const int x[]); 
    void write(FILE * file, const int numParameters) const;
    const int rightHandIndex;
    const int * const x;
};
