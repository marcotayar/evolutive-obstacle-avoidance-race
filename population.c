#include <stdlib.h>
#include <stdio.h>
#include "headers/population.h"
#include "headers/fitness.h"

void initializePopulation(Population *pop) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < COMMANDS_LENGTH; j++) {
            pop->individuals[i].commands[j] = rand() % 3;
        }
        pop->individuals[i].fitness = 0.0f;
    }
}

void evaluatePopulation(Population *pop, char track[TRACK_HEIGHT][TRACK_WIDTH]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        pop->individuals[i].fitness = simulateIndividual(&pop->individuals[i], track);
    }
}

void evolvePopulation(Population *pop, char track[TRACK_HEIGHT][TRACK_WIDTH]) {
    Population nextGen;
    int elitismCount = 20; // Aumentando elitismo

    // Elitismo: Copiar melhores indivíduos para a próxima geração
    for (int i = 0; i < elitismCount; i++) {
        nextGen.individuals[i] = pop->individuals[i];
    }

    for (int i = elitismCount; i < POPULATION_SIZE; i++) {
        Individual parent1 = tournamentSelection(pop);
        Individual parent2 = tournamentSelection(pop);
        crossover(&parent1, &parent2, &nextGen.individuals[i]);
        mutate(&nextGen.individuals[i]);
    }

    *pop = nextGen;
}

Individual tournamentSelection(Population *pop) {
    Individual best;
    best.fitness = -1.0f;

    for (int i = 0; i < TOURNAMENT_SIZE; i++) {
        int idx = rand() % POPULATION_SIZE;
        if (pop->individuals[idx].fitness > best.fitness) {
            best = pop->individuals[idx];
        }
    }

    return best;
}

void mutate(Individual *ind) {
    float mutationRate = 0.01; // Ajuste na taxa de mutação
    for (int i = 0; i < COMMANDS_LENGTH; i++) {
        if ((rand() / (float)RAND_MAX) < mutationRate) {
            ind->commands[i] = rand() % 3;
        }
    }
}

void crossover(Individual *parent1, Individual *parent2, Individual *offspring) {
    for (int i = 0; i < COMMANDS_LENGTH; i++) {
        offspring->commands[i] = (rand() % 2 == 0) ? parent1->commands[i] : parent2->commands[i];
    }
}