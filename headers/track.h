#ifndef TRACK_H
#define TRACK_H

#define TRACK_WIDTH 30
#define TRACK_HEIGHT 150
#define COMMANDS_LENGTH 300

// Estrutura de um indivíduo
typedef struct {
    int commands[COMMANDS_LENGTH]; // Comandos de movimento
    float fitness;                 // Pontuação de fitness
} Individual;

// Cria a pista fixa
void createTrack(char track[TRACK_HEIGHT][TRACK_WIDTH]);

// Imprime a pista no console
void printTrack(char track[TRACK_HEIGHT][TRACK_WIDTH]);

// Simula o movimento de um indivíduo na pista
float simulateIndividual(Individual *ind, char track[TRACK_HEIGHT][TRACK_WIDTH]);

#endif
