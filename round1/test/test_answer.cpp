#include "doctest.h"
#include "problem.h"
#include "answer.h"
#include <cstring>

TEST_CASE("Test if solution writes properly to file") {
    Keyboard conf("iutdjncorepbmyagshkwlxzqvf");
    Problem problem("iroirutdmyxlubr", 15);
    Answer s(conf, problem);

    char buf[256];
    FILE *file = fmemopen(buf, sizeof(buf), "w");
    s.write(file, problem);
    fclose(file);
    REQUIRE(strcmp(buf, "1 9\niutdjncorepbmyagshkwlxzqvf\n") == 0);
}
