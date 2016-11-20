#include "doctest.h"
#include "problem.h"
#include <cstring>

TEST_CASE("Test if problem reads properly from file") {
    char content[] = "30\nmvpmnqgqiuufouoemorbqqhokvfhoe";
    FILE *file = fmemopen(content, strlen(content), "r");
    Problem p(file);
}

