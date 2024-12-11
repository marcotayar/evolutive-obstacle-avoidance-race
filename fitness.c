#include <stdio.h>
#include "headers/fitness.h"

// Calcula a fitness baseado no tempo, penalidades e proximidade
float calculateFitness(int time, int penalty, float distanceFactor, int cima) {
    // Ajuste da fórmula: maior proximidade, menor tempo e penalidades
    // Multiplicamos distanceFactor por um valor maior para dar mais peso
    float score = cima * 500 + 10000 + distanceFactor * 100000.0f - (float)(time*15 + penalty * 60);
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

void saveFitnessData(Population *pop, int generation, FILE *file) {
    if (!file) {
        printf("Erro: arquivo de saída inválido.\n");
        return;
    }

    // Salva a geração e os valores de fitness no arquivo
    fprintf(file, "%d,%.2f,%.2f,%.2f\n",
            generation,
            pop->avgFitness,
            pop->bestFitness,
            pop->worstFitness);
}

