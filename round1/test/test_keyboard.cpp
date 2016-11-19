#include "doctest.h"
#include "keyboard.h"
#include "answer.h"
TEST_CASE("Test keyboard position with default configuration") {
    Configuration defaultConfiguration("qwertyuiopasdfghjklzxcvbnm");
    Keyboard keyboard(defaultConfiguration);

    SUBCASE("Test position of key Q") {
        int index = keyboard.getKeyIndex('q');
        REQUIRE(index == 0);
        REQUIRE(getKeyByIndex(index) == Point2D(85, 140));
    }

    SUBCASE("Test position of key A") {
        int index = keyboard.getKeyIndex('a');
        REQUIRE(index == 10);
        REQUIRE(getKeyByIndex(index) == Point2D(95, 179));
    }

    SUBCASE("Test position of key Z") {
        int index = keyboard.getKeyIndex('z');
        REQUIRE(index == 19);
        REQUIRE(getKeyByIndex(index) == Point2D(122, 219));
    }

    SUBCASE("Test position of key W") {
        int index = keyboard.getKeyIndex('w');
        REQUIRE(index == 1);
        REQUIRE(getKeyByIndex(index) == Point2D(123, 140));
    }

    SUBCASE("Test position of key S") {
        int index = keyboard.getKeyIndex('s');
        REQUIRE(index == 11);
        REQUIRE(getKeyByIndex(index) == Point2D(133, 179));
    }

    SUBCASE("Test position of key X") {
        int index = keyboard.getKeyIndex('x');
        REQUIRE(index == 20);
        REQUIRE(getKeyByIndex(index) == Point2D(160, 219));
    }

    SUBCASE("Test position of key E") {
        int index = keyboard.getKeyIndex('e');
        REQUIRE(index == 2);
        REQUIRE(getKeyByIndex(index) == Point2D(161, 140));
    }

    SUBCASE("Test position of key D") {
        int index = keyboard.getKeyIndex('d');
        REQUIRE(index == 12);
        REQUIRE(getKeyByIndex(index) == Point2D(171, 179));
    }

    SUBCASE("Test position of key C") {
        int index = keyboard.getKeyIndex('c');
        REQUIRE(index == 21);
        REQUIRE(getKeyByIndex(index) == Point2D(198, 219));
    }

    SUBCASE("Test position of key R") {
        int index = keyboard.getKeyIndex('r');
        REQUIRE(index == 3);
        REQUIRE(getKeyByIndex(index) == Point2D(199, 140));
    }

    SUBCASE("Test position of key F") {
        int index = keyboard.getKeyIndex('f');
        REQUIRE(index == 13);
        REQUIRE(getKeyByIndex(index) == Point2D(209, 179));
    }

    SUBCASE("Test position of key V") {
        int index = keyboard.getKeyIndex('v');
        REQUIRE(index == 22);
        REQUIRE(getKeyByIndex(index) == Point2D(236, 219));
    }
    SUBCASE("Test position of key T") {
        int index = keyboard.getKeyIndex('t');
        REQUIRE(index == 4);
        REQUIRE(getKeyByIndex(index) == Point2D(237, 140));
    }

    SUBCASE("Test position of key G") {
        int index = keyboard.getKeyIndex('g');
        REQUIRE(index == 14);
        REQUIRE(getKeyByIndex(index) == Point2D(247, 179));
    }

    SUBCASE("Test position of key B") {
        int index = keyboard.getKeyIndex('b');
        REQUIRE(index == 23);
        REQUIRE(getKeyByIndex(index) == Point2D(275, 219));
    }

    SUBCASE("Test position of key Y") {
        int index = keyboard.getKeyIndex('y');
        REQUIRE(index == 5);
        REQUIRE(getKeyByIndex(index) == Point2D(275, 140));
    }

    SUBCASE("Test position of key H") {
        int index = keyboard.getKeyIndex('h');
        REQUIRE(index == 15);
        REQUIRE(getKeyByIndex(index) == Point2D(285, 179));
    }

    SUBCASE("Test position of key U") {
        int index = keyboard.getKeyIndex('u');
        REQUIRE(index == 6);
        REQUIRE(getKeyByIndex(index) == Point2D(313, 140));
    }

    SUBCASE("Test position of key N") {
        int index = keyboard.getKeyIndex('n');
        REQUIRE(index == 24);
        REQUIRE(getKeyByIndex(index) == Point2D(313, 219));
    }

    SUBCASE("Test position of key J") {
        int index = keyboard.getKeyIndex('j');
        REQUIRE(index == 16);
        REQUIRE(getKeyByIndex(index) == Point2D(324, 179));
    }

    SUBCASE("Test position of key I") {
        int index = keyboard.getKeyIndex('i');
        REQUIRE(index == 7);
        REQUIRE(getKeyByIndex(index) == Point2D(351, 140));
    }

    SUBCASE("Test position of key M") {
        int index = keyboard.getKeyIndex('m');
        REQUIRE(index == 25);
        REQUIRE(getKeyByIndex(index) == Point2D(351, 219));
    }

    SUBCASE("Test position of key K") {
        int index = keyboard.getKeyIndex('k');
        REQUIRE(index == 17);
        REQUIRE(getKeyByIndex(index) == Point2D(362, 179));
    }

    SUBCASE("Test position of key O") {
        int index = keyboard.getKeyIndex('o');
        REQUIRE(index == 8);
        REQUIRE(getKeyByIndex(index) == Point2D(389, 140));
    }

    SUBCASE("Test position of key L") {
        int index = keyboard.getKeyIndex('l');
        REQUIRE(index == 18);
        REQUIRE(getKeyByIndex(index) == Point2D(400, 179));
    }

    SUBCASE("Test position of key P") {
        int index = keyboard.getKeyIndex('p');
        REQUIRE(index == 9);
        REQUIRE(getKeyByIndex(index) == Point2D(427, 140));
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
    Point2D leftFinger   = getKeyByIndex(fingers.left);
    Point2D rightFinger  = getKeyByIndex(fingers.right);
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
    Point2D leftFinger = getKeyByIndex(fingers.left);
    Point2D rightFinger = getKeyByIndex(fingers.right);
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


