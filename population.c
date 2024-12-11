#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/population.h"
#include "headers/fitness.h"

// Função de comparação para qsort, ordena decrescente por fitness
static int compareIndividualsByFitness(const void *a, const void *b) {
    const Individual *indA = (const Individual *)a;
    const Individual *indB = (const Individual *)b;
    if (indB->fitness > indA->fitness) return 1;
    else if (indB->fitness < indA->fitness) return -1;
    return 0;
}

static int lastFinalX = -1; // Última posição final X
static int lastFinalY = -1; // Última posição final Y
static int stagnantPositionGenerations = 0; // Gerações sem mudança na posição final
const int POSITION_STAGNATION_LIMIT = 100;  // Limite de gerações com posição final estagnada

// Função para obter a posição final de um indivíduo
void getFinalPosition(Individual *ind, char track[TRACK_HEIGHT][TRACK_WIDTH], int *finalX, int *finalY, int *reachedDestination) {
    int x = 0, y = 0; // Posição inicial
    *reachedDestination = 0; // Inicialmente, não atingiu o destino

    for (int i = 0; i < COMMANDS_LENGTH; i++) {
        switch (ind->commands[i]) {
            case 0: if (y < TRACK_HEIGHT - 1) y++; break; // Baixo
            case 1: if (x > 0) x--; break;               // Esquerda
            case 2: if (x < TRACK_WIDTH - 1) x++; break; // Direita
        }
        if (track[y][x] == 'F') {
            *reachedDestination = 1; // Alcançou o destino
            break;
        }
    }
    *finalX = x;
    *finalY = y;
}

// Ordena a população por fitness (decrescente)
void sortPopulationByFitness(Population *pop) {
    qsort(pop->individuals, POPULATION_SIZE, sizeof(Individual), compareIndividualsByFitness);
}

// Inicializa a população com comandos aleatórios
void initializePopulation(Population *pop) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < COMMANDS_LENGTH; j++) {
            pop->individuals[i].commands[j] = rand() % 3;
        }
        pop->individuals[i].fitness = 0.0f;
    }
}

// Avalia a fitness de todos os indivíduos na população
void evaluatePopulation(Population *pop, char track[TRACK_HEIGHT][TRACK_WIDTH]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        pop->individuals[i].fitness = simulateIndividual(&pop->individuals[i], track);
    }
}

// Seleção por torneio
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

// Cruzamento entre dois pais para gerar um descendente
void crossover(Individual *parent1, Individual *parent2, Individual *offspring) {
    for (int i = 0; i < COMMANDS_LENGTH; i++) {
        offspring->commands[i] = (rand() % 2 == 0) ? parent1->commands[i] : parent2->commands[i];
    }
}

// Mutação de um indivíduo
void mutate(Individual *ind) {
    float mutationRate = 0.02f; // Taxa de mutação de 1%
    for (int i = 0; i < COMMANDS_LENGTH; i++) {
        if (((float)rand() / (float)RAND_MAX) < mutationRate) {
            ind->commands[i] = rand() % 3;
        }
    }
}

void evolvePopulation(Population *pop, char track[TRACK_HEIGHT][TRACK_WIDTH]) {
    Population nextGen;
    int elitismCount = 20; // Número de melhores indivíduos a serem mantidos

    // Obter a posição final do melhor indivíduo
    int currentFinalX, currentFinalY, reachedDestination;
    getFinalPosition(&pop->individuals[0], track, &currentFinalX, &currentFinalY, &reachedDestination);

    // Verificar estagnação da posição final
    if (currentFinalX == lastFinalX && currentFinalY == lastFinalY && !reachedDestination) {
        stagnantPositionGenerations++;
    } else {
        stagnantPositionGenerations = 0; // Resetar contagem se houve mudança
        lastFinalX = currentFinalX;
        lastFinalY = currentFinalY;
    }

    // Reinicia a população se a posição final estiver estagnada e não for o destino
    if (stagnantPositionGenerations >= POSITION_STAGNATION_LIMIT) {
        printf("Estagnação da posição final detectada por %d gerações (não é o destino). Reiniciando a população...\n", POSITION_STAGNATION_LIMIT);
        initializePopulation(pop);
        stagnantPositionGenerations = 0;
        lastFinalX = -1;
        lastFinalY = -1;
        return; // Encerrar evolução para esta geração
    }

    // Elite: copia os melhores
    for (int i = 0; i < elitismCount; i++) {
        nextGen.individuals[i] = pop->individuals[i];
    }

    // Resto: torneio, cruzamento e mutação
    for (int i = elitismCount; i < POPULATION_SIZE; i++) {
        Individual parent1 = tournamentSelection(pop);
        Individual parent2 = tournamentSelection(pop);
        crossover(&parent1, &parent2, &nextGen.individuals[i]);
        mutate(&nextGen.individuals[i]);
    }

    // Substituir a população antiga pela nova
    for (int i = 0; i < POPULATION_SIZE; i++) {
        pop->individuals[i] = nextGen.individuals[i];
    }
}

