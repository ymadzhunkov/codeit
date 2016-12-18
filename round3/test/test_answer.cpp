#include "doctest.h"
#include "problem.h"
#include "answer.h"
#include <string>

template <typename T, std::size_t N>
constexpr std::size_t countof(T const (&)[N]) noexcept {
    return N;
}

TEST_CASE("Test if solution writes properly to file") {
    const int x[] = { 713, 984, 870, 942 };
    Answer s(0, x);
    char buf[256];
    s.write(fmemopen(buf, sizeof(buf), "w"), countof(x));
    REQUIRE(std::string(buf) == std::string("1\n713 984 870 942 \n"));
}

TEST_CASE("Test if solution writes properly to file") {
    const int x[] = { 984, 870, 942 };
    Answer s(7, x);
    char buf[256];
    s.write(fmemopen(buf, sizeof(buf), "w"), countof(x));
    REQUIRE(std::string(buf) == std::string("8\n984 870 942 \n"));
}
