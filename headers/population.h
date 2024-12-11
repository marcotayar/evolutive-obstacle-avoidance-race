#ifndef POPULATION_H
#define POPULATION_H

#define POPULATION_SIZE 1200
#define TOURNAMENT_SIZE 10

#include "track.h"

// Estrutura da população
typedef struct Population {
    Individual individuals[POPULATION_SIZE];
    float avgFitness;
    float bestFitness;
    float worstFitness;
} Population;

// Inicializa a população com comandos aleatórios
void initializePopulation(Population *pop);

// Avalia a fitness de todos os indivíduos na população
void evaluatePopulation(Population *pop, char track[TRACK_HEIGHT][TRACK_WIDTH]);

// Evolui a população para a próxima geração
void evolvePopulation(Population *pop, char track[TRACK_HEIGHT][TRACK_WIDTH]);

// Seleção por torneio
Individual tournamentSelection(Population *pop);

// Funções de mutação e cruzamento
void mutate(Individual *ind);
void crossover(Individual *parent1, Individual *parent2, Individual *offspring);

// Ordena a população por fitness (decrescente)
void sortPopulationByFitness(Population *pop);

#endif
