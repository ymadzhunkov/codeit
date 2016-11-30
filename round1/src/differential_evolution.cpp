#include "differential_evolution.h"
#include <random>

void sampleAgents(int sampledAgentsIndecies[4],
                  std::default_random_engine &generator) {
    for (int numSelected = 1; numSelected < 4; numSelected++) {
        int &res = sampledAgentsIndecies[numSelected];
        for (res = -1; res == -1; ) {
            res = generator() % Population::size;
            for (int i = 0; i < numSelected; i++)
                if (sampledAgentsIndecies[i] == res) res = -1;
        }
    }
}

void sampleCrossover(float u[Individual::degreesOfFreedom],
                     std::default_random_engine &generator) {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < Individual::degreesOfFreedom; i++) 
        u[i] = distribution(generator);
    int r = generator() % Individual::degreesOfFreedom;
    u[r] = -1.0; // any negative number can do
}

Individual
generateCandidate(const EvelutionParams params,
                  const Individual agents[], const int selected[4],
                  const float u[Individual::degreesOfFreedom]) {
    const float *x = agents[selected[0]].coordinates;
    const float *a = agents[selected[1]].coordinates;
    const float *b = agents[selected[2]].coordinates;
    const float *c = agents[selected[3]].coordinates;

    const float CP = params.crossoverProbability;
    const float DW = params.differentialWeight;

    Individual res;
    for (int i = 0; i < Individual::degreesOfFreedom; i++)
        res.coordinates[i] =
            u[i] < CP ? a[i] + DW * (b[i] - c[i]) : x[i];

    return res;
}

void printPopulation(FILE *file, const Population &population) {
    for (int i = 0; i < Population::size; i++) {
        fprintf(file, "Agent %d, fitness %f, coord = ", i, 
        population.fitness[i]);
        for (int j = 0; j < Individual::degreesOfFreedom; j++) 
            fprintf(file, "%f, ", population.agents[i].coordinates[j]);
        fprintf(file, "\n");
    }
}

void evelutionStep(const EvelutionParams params,
                   std::function<float(const Individual &)> func,
                   Population &population,
                   std::default_random_engine &generator) {
    for (int i = 0; i < Individual::degreesOfFreedom; i++) {
        int sampledAgentsIndecies[4] = { i, 0, 0, 0 };
        sampleAgents(sampledAgentsIndecies, generator);

        float u[Individual::degreesOfFreedom]; 
        sampleCrossover(u, generator);

        Individual candidate = generateCandidate(
            params, population.agents, sampledAgentsIndecies, u);

        float candidateFitness = func(candidate);
        if (candidateFitness < population.fitness[i]) {
            population.agents[i] = candidate;
            population.fitness[i] = candidateFitness;
        }
    }
    printPopulation(stdout, population);
}

Individual randomIndividual(std::default_random_engine &generator) {
    std::uniform_real_distribution<double> distribution(0.0, 40.0);
    Individual res;
    for (int i = 0; i < Individual::degreesOfFreedom; i++)
        res.coordinates[i] = distribution(generator);
    return res;
}

Individual findBest(const Population &population) {
    int pos = 0;
    for (int i = 1; i < Population::size; i++)
        pos =
            population.fitness[i] < population.fitness[pos] ? i : pos;
    return population.agents[pos];
}

Population
initializePopulation(std::function<float(const Individual &)> func,
                     std::default_random_engine &generator) {
    Population res;
    for (int i = 0; i < Population::size; i++) {
        res.agents[i] = randomIndividual(generator);
        res.fitness[i] = func(res.agents[i]);
    }
    return res;
}


Individual
differentialEvolution(const EvelutionParams params,
                      std::function<float(const Individual &)> func) {
    std::default_random_engine generator(7878);
    Population population = initializePopulation(func, generator);
    for (int i = 0; i < 1024; i++) {
        evelutionStep(params, func, population, generator);
    }
    return findBest(population);
}

