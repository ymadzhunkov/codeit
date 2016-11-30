#include "differential_evolution.h"
#include "doctest.h"
#include <random>

TEST_CASE("test generate candidate") {
    EvelutionParams params;
    params.differentialWeight = 1.1;
    params.crossoverProbability = 0.2;
    const float crossover = params.crossoverProbability - 1e-5;
    const float nocrossover = params.crossoverProbability + 1e-5;
    int selected[4] = {0, 1, 2, 3};
    Individual agents[4];
    agents[selected[0]].coordinates[0] = 0.1;
    agents[selected[1]].coordinates[0] = 0.4;
    agents[selected[2]].coordinates[0] = 0.7;
    agents[selected[3]].coordinates[0] = 0.8;

    agents[selected[0]].coordinates[1] = 0.2;
    agents[selected[1]].coordinates[1] = 0.5;
    agents[selected[2]].coordinates[1] = 1.0;
    agents[selected[3]].coordinates[1] = 1.1;

    agents[selected[0]].coordinates[2] = 0.3;
    agents[selected[1]].coordinates[2] = 0.6;
    agents[selected[2]].coordinates[2] = 0.9;
    agents[selected[3]].coordinates[2] = 1.4;
    using doctest::Approx;

    SUBCASE("No crossover") {
        float u[Individual::degreesOfFreedom] = { nocrossover,
                                                  nocrossover,
                                                  nocrossover };
        Individual a = generateCandidate(params, agents, selected, u);
        REQUIRE(a.coordinates[0] == Approx(0.10f).epsilon(1e-5f));
        REQUIRE(a.coordinates[1] == Approx(0.20f).epsilon(1e-5f));
        REQUIRE(a.coordinates[2] == Approx(0.30f).epsilon(1e-5f));
    }

    SUBCASE("crossover at 0") {
        float u[Individual::degreesOfFreedom] = { crossover,
                                                  crossover,
                                                  crossover };
        Individual a = generateCandidate(params, agents, selected, u);
        REQUIRE(a.coordinates[0] == Approx(0.29f).epsilon(1e-5f));
        REQUIRE(a.coordinates[1] == Approx(0.39f).epsilon(1e-5f));
        REQUIRE(a.coordinates[2] == Approx(0.05f).epsilon(1e-5f));
    }
}

TEST_CASE("Testing sampling agents") {
    int samples[4] = { 3, 0, 0, 0 };

    SUBCASE ("Seed 7878") {
        std::default_random_engine generator(7878);
        sampleAgents(samples, generator);
    }

    SUBCASE ("Seed 1234") {
        std::default_random_engine generator(1234);
        sampleAgents(samples, generator);
    }

    REQUIRE(samples[0] == 3);
    REQUIRE(samples[1] < Population::size);
    REQUIRE(samples[2] < Population::size);
    REQUIRE(samples[3] < Population::size);
    REQUIRE(samples[1] >= 0);
    REQUIRE(samples[2] >= 0);
    REQUIRE(samples[3] >= 0);

    REQUIRE(samples[1] != samples[0]);
    REQUIRE(samples[2] != samples[0]);
    REQUIRE(samples[3] != samples[0]);
    REQUIRE(samples[2] != samples[1]);
    REQUIRE(samples[3] != samples[1]);
    REQUIRE(samples[3] != samples[2]);

}
