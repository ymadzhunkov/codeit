#include "doctest.h"
#include "keyboard.h"
#include "answer.h"
TEST_CASE("Test keyboard position with default configuration") {
    Configuration defaultConfiguration("qwertyuiopasdfghjklzxcvbnm");
    Keyboard keyboard(defaultConfiguration);
    SUBCASE("Test position of key Q") {
        REQUIRE(keyboard.getPosition('q') == Point2D(85, 140));
    }

    SUBCASE("Test position of key A") {
        REQUIRE(keyboard.getPosition('a') == Point2D(95, 179));
    }

    SUBCASE("Test position of key Z") {
        REQUIRE(keyboard.getPosition('z') == Point2D(122, 219));
    }

    SUBCASE("Test position of key W") {
        REQUIRE(keyboard.getPosition('w') == Point2D(123, 140));
    }

    SUBCASE("Test position of key S") {
        REQUIRE(keyboard.getPosition('s') == Point2D(133, 179));
    }

    SUBCASE("Test position of key X") {
        REQUIRE(keyboard.getPosition('x') == Point2D(160, 219));
    }

    SUBCASE("Test position of key E") {
        REQUIRE(keyboard.getPosition('e') == Point2D(161, 140));
    }

    SUBCASE("Test position of key D") {
        REQUIRE(keyboard.getPosition('d') == Point2D(171, 179));
    }

    SUBCASE("Test position of key C") {
        REQUIRE(keyboard.getPosition('c') == Point2D(198, 219));
    }

    SUBCASE("Test position of key R") {
        REQUIRE(keyboard.getPosition('r') == Point2D(199, 140));
    }

    SUBCASE("Test position of key F") {
        REQUIRE(keyboard.getPosition('f') == Point2D(209, 179));
    }

    SUBCASE("Test position of key V") {
        REQUIRE(keyboard.getPosition('v') == Point2D(236, 219));
    }
    SUBCASE("Test position of key T") {
        REQUIRE(keyboard.getPosition('t') == Point2D(237, 140));
    }

    SUBCASE("Test position of key G") {
        REQUIRE(keyboard.getPosition('g') == Point2D(247, 179));
    }

    SUBCASE("Test position of key B") {
        REQUIRE(keyboard.getPosition('b') == Point2D(275, 219));
    }

    SUBCASE("Test position of key Y") {
        REQUIRE(keyboard.getPosition('y') == Point2D(275, 140));
    }

    SUBCASE("Test position of key H") {
        REQUIRE(keyboard.getPosition('h') == Point2D(285, 179));
    }

    SUBCASE("Test position of key U") {
        REQUIRE(keyboard.getPosition('u') == Point2D(313, 140));
    }

    SUBCASE("Test position of key N") {
        REQUIRE(keyboard.getPosition('n') == Point2D(313, 219));
    }

    SUBCASE("Test position of key J") {
        REQUIRE(keyboard.getPosition('j') == Point2D(324, 179));
    }

    SUBCASE("Test position of key I") {
        REQUIRE(keyboard.getPosition('i') == Point2D(351, 140));
    }

    SUBCASE("Test position of key M") {
        REQUIRE(keyboard.getPosition('m') == Point2D(351, 219));
    }

    SUBCASE("Test position of key K") {
        REQUIRE(keyboard.getPosition('k') == Point2D(362, 179));
    }

    SUBCASE("Test position of key O") {
        REQUIRE(keyboard.getPosition('o') == Point2D(389, 140));
    }

    SUBCASE("Test position of key L") {
        REQUIRE(keyboard.getPosition('l') == Point2D(400, 179));
    }

    SUBCASE("Test position of key P") {
        REQUIRE(keyboard.getPosition('p') == Point2D(427, 140));
    }


}

TEST_CASE("Test fingers position with example configuration") {
    Configuration defaultConfiguration("qwertyuiopasdfghjklzxcvbnm");
    Keyboard keyboard(defaultConfiguration);
    Fingers fingers;
    SUBCASE("B first") {
        fingers = keyboard.initPosition(Problem("by", 2));
        REQUIRE(fingers.left == 23);
        REQUIRE(fingers.right != 5);
    }
    SUBCASE("Y first") {
        fingers = keyboard.initPosition(Problem("yb", 2));
        REQUIRE(fingers.left == 5);
        REQUIRE(fingers.right != 23);
    }
    SUBCASE("Y first") {
        fingers = keyboard.initPosition(Problem("yyyb", 2));
        REQUIRE(fingers.left == 5);
        REQUIRE(fingers.right != 23);
    }
    REQUIRE(fingers.right >= 0);
    REQUIRE(fingers.right <= 25);
    Point2D leftFinger   = keyboard.getKeyByIndex(fingers.left);
    Point2D rightFinger  = keyboard.getKeyByIndex(fingers.right);
    REQUIRE(leftFinger.x < rightFinger.x);
}

TEST_CASE("Test fingers position with example configuration") {
    Keyboard keyboard(Configuration("iutdjncorepbmyagshkwlxzqvf"));
    Fingers fingers;
    SUBCASE("input length 1") {
        fingers = keyboard.initPosition(Problem("i", 1));
        REQUIRE(fingers.left == 0);
        REQUIRE(fingers.right >= 0);
        REQUIRE(fingers.right <= 25);
    }

    SUBCASE("input length 1") {
        fingers = keyboard.initPosition(Problem("e", 1));
        REQUIRE(fingers.right == 9);
        REQUIRE(fingers.left >= 0);
        REQUIRE(fingers.left <= 25);
    }

    SUBCASE("input at both ends of length 2") {
        SUBCASE("left first") {
            fingers = keyboard.initPosition(Problem("te", 2));
        }
        SUBCASE("right first") {
            fingers = keyboard.initPosition(Problem("et", 2));
        }
        REQUIRE(fingers.left == 2);
        REQUIRE(fingers.right == 9);
    }

    SUBCASE("input almost on top of each other length 2") {
        SUBCASE("U first") {
            fingers = keyboard.initPosition(Problem("uw", 2));
        }
        SUBCASE("W first") {
            fingers = keyboard.initPosition(Problem("wu", 2));
        }
        REQUIRE(fingers.left == 19);
        REQUIRE(fingers.right == 1);
    }
    Point2D leftFinger = keyboard.getKeyByIndex(fingers.left);
    Point2D rightFinger = keyboard.getKeyByIndex(fingers.right);
    REQUIRE(leftFinger.x < rightFinger.x);

}

TEST_CASE("Test computing distance with example configuration") {
    Keyboard keyboard(Configuration("iutdjncorepbmyagshkwlxzqvf"));
    const char * input = "iroirutdmyxlubr";
    Fingers fingers = keyboard.initPosition(Problem(input, 2));

    SUBCASE("Use first 2 symbols") {
        REQUIRE(0 == keyboard.distance(Problem(input, 2), fingers));
    }

    SUBCASE("Use first 3 symbols") {
        const int d = keyboard.dist(keyboard.getKeyIndex('r'),
                                    keyboard.getKeyIndex('o'));
        REQUIRE(38 == d);
        REQUIRE(38 == keyboard.distance(Problem(input, 3), fingers));
    }

    SUBCASE("Use first 4 symbols") {
        REQUIRE(38 == keyboard.distance(Problem(input, 4), fingers));
    }

    SUBCASE("Use first 5 symbols") {
        const int d = keyboard.dist(keyboard.getKeyIndex('o'),
                                    keyboard.getKeyIndex('r'));
        
        REQUIRE(38 == d);
        REQUIRE(76 == keyboard.distance(Problem(input, 5), fingers));
    }
    SUBCASE("Use first 6 symbols") {
        const int d = keyboard.dist(keyboard.getKeyIndex('i'),
                                    keyboard.getKeyIndex('u'));
        
        REQUIRE(38 == d);
        REQUIRE(3 * 38 == keyboard.distance(Problem(input, 6), fingers));
    }

    SUBCASE("Use first 7 symbols") {
        const int d = keyboard.dist(keyboard.getKeyIndex('u'),
                                    keyboard.getKeyIndex('t'));
        
        REQUIRE(38 == d);
        REQUIRE(4 * 38 == keyboard.distance(Problem(input, 7), fingers));
    }

    SUBCASE("Use first 9 symbols") {
        const int d = keyboard.dist(keyboard.getKeyIndex('d'),
                                    keyboard.getKeyIndex('m'));
        REQUIRE(48 == d);
        REQUIRE(5 * 38 + 48== keyboard.distance(Problem(input, 9), fingers));
    }

    SUBCASE("Use first 15 symbols") {
        REQUIRE(482 == keyboard.distance(Problem(input, 15), fingers));
    }
}

TEST_CASE("Test computing distance handles finger crossing") {
    Keyboard keyboard(Configuration("qwertyuiopasdfghjklzxcvbnm"));

    SUBCASE("Use vtr") {
        Problem p("vtr", 3);
        Fingers fingers = keyboard.initPosition(p);
        const int d = keyboard.dist(keyboard.getKeyIndex('v'),
                                    keyboard.getKeyIndex('r'));
        REQUIRE(d == keyboard.distance(p, fingers));
    }

    SUBCASE("Use bty") {
        Problem p("bty", 3);
        Fingers fingers = keyboard.initPosition(p);
        const int d = keyboard.dist(keyboard.getKeyIndex('b'),
                                    keyboard.getKeyIndex('y'));
        REQUIRE(d == keyboard.distance(p, fingers));
    }

}


TEST_CASE("Test if mutation of solution leads to differnt solution") {
    const char * input = "helloworldhelloworld";

    Problem p(input, 20);
    Answer sol(Configuration("iutdjncorepbmyagshkwlxzqvf"), p);

    auto rnd = std::minstd_rand(1234);
    Answer sol2(rnd, sol, p);
    REQUIRE(sol2.dist != sol.dist);

    sol2 = sol;

    REQUIRE(sol2.dist == sol.dist);
    
}


