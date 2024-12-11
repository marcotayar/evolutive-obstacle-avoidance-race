#include <stdio.h>
#include <string.h>
#include "headers/track.h"

void createTrack(char track[TRACK_HEIGHT][TRACK_WIDTH]) {
    const char fixedTrack[TRACK_HEIGHT][TRACK_WIDTH + 1] = {
        "S.............................",
        "..............................",
        "...X.....X....................",
        "..................X...........",
        "..............X.........X.....",
        "..........................X...",
        ".....X.X.............X........",
        "......X.......................",
        "..........X...................",
        "..............X...............",
        "...........X.....X............",
        ".......................X......",
        ".............X........X.......",
        "...............X..............",
        "..............X...............",
        "....X.........................",
        ".....................X........",
        "..............X...............",
        "..............................",
        "...X.............X............",
        "..............X...............",
        "...........X..................",
        ".............X................",
        "..............X...............",
        "..............X...............",
        "..............................",
        "..............................",
        ".............X................",
        "..............X...............",
        "...X................X.........",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X.....X.........",
        "..............................",
        "..............X...............",
        "..............X.....X.........",
        "..............X...............",
        ".....X........................",
        "..............X...............",
        "..............................",
        ".....X.............X..........",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............................",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        ".........................F....",
    };

    for (int i = 0; i < TRACK_HEIGHT; i++) {
        strncpy(track[i], fixedTrack[i], TRACK_WIDTH);
    }
}

void printTrack(char track[TRACK_HEIGHT][TRACK_WIDTH]) {
    for (int i = 0; i < TRACK_HEIGHT; i++) {
        for (int j = 0; j < TRACK_WIDTH; j++) {
            putchar(track[i][j]);
        }
        putchar('\n');
    }
}

float simulateIndividual(Individual *ind, char track[TRACK_HEIGHT][TRACK_WIDTH]) {
    int x = 0, y = 0; // Start at the top-left corner
    int time = 0, penalty = 0, revisited = 0;
    int visited[TRACK_HEIGHT][TRACK_WIDTH] = {0}; // Track visited cells

    for (int i = 0; i < COMMANDS_LENGTH; i++) {
        if (track[y][x] == 'F') break; // Reached the finish line

        // Mark the current cell as visited
        visited[y][x]++;
        if (visited[y][x] > 1) revisited++; // Penalize revisiting cells

        // Execute the command
        switch (ind->commands[i]) {
            case 0: if (y > 0) y--; break;                     // Move up
            case 1: if (y < TRACK_HEIGHT - 1) y++; break;      // Move down
            case 2: if (x < TRACK_WIDTH - 1) x++; break;       // Move right
        }

        // Check for obstacles
        if (track[y][x] == 'X') penalty++;

        // Increment time
        time++;
    }

    // Calculate distance to the finish line (Manhattan distance)
    int distance = TRACK_HEIGHT - 1 - y + TRACK_WIDTH - 1 - x;

    // Enhanced fitness calculation to include revisits and distance weighting
    return calculateFitness(time, penalty + revisited, TRACK_HEIGHT + TRACK_WIDTH - distance);
}

