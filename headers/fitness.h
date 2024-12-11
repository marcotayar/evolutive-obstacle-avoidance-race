#ifndef FITNESS_H
#define FITNESS_H

#include "population.h"

// Calcula a fitness baseado no tempo, penalidades e proximidade
float calculateFitness(int time, int penalty, float distanceFactor, int cima);

// Imprime estatísticas de fitness da população
void printFitnessStats(Population *pop, int generation);

#endif
