#include <stdio.h>
#include <stdlib.h>
#include "headers/population.h"
#include "headers/fitness.h"
#include "headers/track.h"

int main() {
    char track[TRACK_HEIGHT][TRACK_WIDTH];
    Population population;

    createTrack(track);
    printTrack(track);

    initializePopulation(&population);

    for (int generation = 0; generation < 1000; generation++) {
        evaluatePopulation(&population, track);
        printFitnessStats(&population, generation);
        evolvePopulation(&population, track);
    }

    return 0;
}

