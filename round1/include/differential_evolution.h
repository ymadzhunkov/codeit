#pragma once
#include <functional>
#include <random>

struct Individual {
    enum {
        degreesOfFreedom = 3
    };
    float coordinates[degreesOfFreedom];
};

struct Population {
    enum {
        size = 10
    };
    Individual agents[size];
    float fitness[size];
};

struct EvelutionParams {
    float differentialWeight;
    float crossoverProbability;
};

Individual
differentialEvolution(const EvelutionParams params,
                      std::function<float(const Individual &)> func);

Individual
generateCandidate(const EvelutionParams params,
                  const Individual agents[], const int selected[4],
                  const float u[Individual::degreesOfFreedom]);

void sampleAgents(int sampledAgentsIndecies[4],
                  std::default_random_engine &generator);
