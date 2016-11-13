#include "problem.h"
#include <fstream>
#include <iostream>

std::string readInput() {
    std::ifstream fin("keyboard.in");
    std::string s;
    std::getline(fin, s);
    std::getline(fin, s);
    return s;
}

