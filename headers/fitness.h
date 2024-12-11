#ifndef FITNESS_H
#define FITNESS_H

#include "population.h"

float calculateFitness(int time, int penalty, int distance);
void evaluateFitness(Population *pop, char track[TRACK_HEIGHT][TRACK_WIDTH]);
void printFitnessStats(Population *pop, int generation);

#endif
