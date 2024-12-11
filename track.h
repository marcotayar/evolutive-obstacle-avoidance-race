#ifndef TRACK_H
#define TRACK_H

#define TRACK_WIDTH 50
#define TRACK_HEIGHT 150

#define COMMANDS_LENGTH 300

typedef struct {
    int commands[COMMANDS_LENGTH]; // Movement commands
    float fitness;                 // Fitness score
} Individual;

void createTrack(char track[TRACK_HEIGHT][TRACK_WIDTH]);
void printTrack(char track[TRACK_HEIGHT][TRACK_WIDTH]);
float simulateIndividual(Individual *ind, char track[TRACK_HEIGHT][TRACK_WIDTH]);
float calculateFitness(int time, int penalty, int distance);

#endif

