#include <stdio.h>
#include "headers/fitness.h"

// Calcula a fitness baseado no tempo, penalidades e proximidade
float calculateFitness(int time, int penalty, float distanceFactor) {
    // Ajuste da fórmula: maior proximidade, menor tempo e penalidades
    // Multiplicamos distanceFactor por um valor maior para dar mais peso
    float score = distanceFactor * 1000.0f - (float)(time + penalty * 10);
    if (score < 0.0f) score = 0.0f; // Evita fitness negativo
    return score;
}

// Imprime estatísticas de fitness da população
void printFitnessStats(Population *pop, int generation) {
    float sumFitness = 0.0f;
    float bestFitness = -1.0f;
    float worstFitness = 1000000.0f; // Valor grande para iniciar

    for (int i = 0; i < POPULATION_SIZE; i++) {
        float fitness = pop->individuals[i].fitness;
        sumFitness += fitness;
        if (fitness > bestFitness) bestFitness = fitness;
        if (fitness < worstFitness) worstFitness = fitness;
    }

    pop->avgFitness = sumFitness / POPULATION_SIZE;
    pop->bestFitness = bestFitness;
    pop->worstFitness = worstFitness;

    printf("Geração %d: Média: %.2f, Melhor: %.2f, Pior: %.2f\n", generation, pop->avgFitness, pop->bestFitness, pop->worstFitness);
}
