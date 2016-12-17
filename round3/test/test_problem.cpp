#include "doctest.h"
#include "problem.h"
#include <cstring>

TEST_CASE("Test if problem reads properly from file") {
    char content[] =
        "5 4\n"
        "6456  14482 80443 91712 856827 404250\n"
        "46603 85084 90886 43276 359810 220421\n"
        "73805 76890 42862 62163 621170 795841\n"
        "6324  15062 37884 17771 890601 261041\n"
        "53674 13346 95893 53116 150825 207655\n"
        "1\n"
        "175231511 46012106 293888266 414081012 725440535";
    FILE *file = fmemopen(content, strlen(content), "r");
    Problem p(file);
    REQUIRE(p.numEquations == 5);
    REQUIRE(p.numParameters == 4);
    REQUIRE(p.rewards[0].exact == 856827);
    REQUIRE(p.rewards[1].exact == 359810);
    REQUIRE(p.rewards[2].exact == 621170);
    REQUIRE(p.rewards[3].exact == 890601);
    REQUIRE(p.rewards[4].exact == 150825);
    REQUIRE(p.rewards[0].approx == 404250);
    REQUIRE(p.rewards[1].approx == 220421);
    REQUIRE(p.rewards[2].approx == 795841);
    REQUIRE(p.rewards[3].approx == 261041);
    REQUIRE(p.rewards[4].approx == 207655);
}

