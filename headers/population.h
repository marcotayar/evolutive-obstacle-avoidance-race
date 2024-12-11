#ifndef POPULATION_H
#define POPULATION_H

#define POPULATION_SIZE 3000
#define TOURNAMENT_SIZE 30

#include "track.h"


typedef struct {
    Individual individuals[POPULATION_SIZE];
    float avgFitness;
    float bestFitness;
    float worstFitness;
} Population;

void initializePopulation(Population *pop);
void evaluatePopulation(Population *pop, char track[TRACK_HEIGHT][TRACK_WIDTH]);
void evolvePopulation(Population *pop, char track[TRACK_HEIGHT][TRACK_WIDTH]);
Individual tournamentSelection(Population *pop);
void mutate(Individual *ind);
void crossover(Individual *parent1, Individual *parent2, Individual *offspring);

#endif
