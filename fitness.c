#include <stdio.h>
#include "headers/fitness.h"

float calculateFitness(int time, int penalty, int distance) {
    // Ajustando a fórmula para priorizar menos penalidades e maior distância
    if (time + penalty == 0) return 0.0;
    return distance / (float)(time + penalty * 2);
}

void evaluateFitness(Population *pop, char track[TRACK_HEIGHT][TRACK_WIDTH]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        int result = simulateIndividual(&pop->individuals[i], track);
        pop->individuals[i].fitness = result > 0 ? result : -1.0f;
    }
}

void printFitnessStats(Population *pop, int generation) {
    float sumFitness = 0.0f;
    float bestFitness = -1.0f;
    float worstFitness = 10000.0f;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        float fitness = pop->individuals[i].fitness;
        sumFitness += fitness;
        if (fitness > bestFitness) bestFitness = fitness;
        if (fitness < worstFitness) worstFitness = fitness;
    }

    pop->avgFitness = sumFitness / POPULATION_SIZE;
    pop->bestFitness = bestFitness;
    pop->worstFitness = worstFitness;

    printf("Generation %d: Avg %.2f, Best %.2f, Worst %.2f\n", generation, pop->avgFitness, pop->bestFitness, pop->worstFitness);
}