#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "headers/track.h"
#include "headers/fitness.h" // Para acessar calculateFitness

// Cria a pista fixa a partir de uma matriz de caracteres
void createTrack(char track[TRACK_HEIGHT][TRACK_WIDTH]) {
    const char fixedTrack[TRACK_HEIGHT][TRACK_WIDTH + 1] = {
        "S.............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
        "..............................",
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
        "....................X.........",
        "...........X..................",
        ".....X........................",
        "..............X...............",
        "..............................",
        ".....X.............X..........",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "..............X...............",
        "......X.......................",
        "...........................X..",
        "......................X.......",
        ".......................X......",
        ".................X............",
        ".........X....................",
        "....................X.........",
        "...........X..................",
        "..................X...........",
        "...........................X..",
        "..........................X...",
        "..............X...............",
        "....................X.........",
        ".......X......................",
        "..................X...........",
        "...........................X..",
        ".........X....................",
        "........................X.....",
        "................X.............",
        "...........X..................",
        "..............X...............",
        ".........X....................",
        ".......X......................",
        "..............X...............",
        "..................X...........",
        "....X.........................",
        "...........X..................",
        "..............X...............",
        ".........X....................",
        "....................X.........",
        "..............X...............",
        "..........................X...",
        "..............X...............",
        ".......................X......",
        "...X..........................",
        ".................X............",
        ".........X....................",
        "............X.................",
        "...................X..........",
        "...........X..................",
        "..........................X...",
        ".............X................",
        "........X.....................",
        "..................X...........",
        "..............X...............",
        ".......X......................",
        "..............X...............",
        "..............X...............",
        ".....................X........",
        "..X...........................",
        "............X.................",
        "..................X...........",
        ".........X....................",
        "..............X...............",
        "......................X.......",
        "..................X...........",
        ".........X....................",
        "............X.................",
        "..................X...........",
        "...X..........................",
        "............X.................",
        "..............X...............",
        ".........X....................",
        "......X.......................",
        "..................X...........",
        "..............X...............",
        "...........................X..",
        "...................X..........",
        ".........X....................",
        "................X.............",
        "...........X..................",
        ".......X......................",
        "....................X.........",
        ".........................X....",
        ".............X................",
        "..............................",
        ".........X....................",
        "...........................X..",
        "...X..........................",
        ".......X......................",
        ".....................X........",
        ".........................F....",
    };

    for (int i = 0; i < TRACK_HEIGHT; i++) {
        strncpy(track[i], fixedTrack[i], TRACK_WIDTH);
    }
}

// Função para imprimir a pista no console
void printTrack(char track[TRACK_HEIGHT][TRACK_WIDTH]) {
    for (int i = 0; i < TRACK_HEIGHT; i++) {
        for (int j = 0; j < TRACK_WIDTH; j++) {
            putchar(track[i][j]);
        }
        putchar('\n');
    }
}

// Simula o movimento de um indivíduo na pista
float simulateIndividual(Individual *ind, char track[TRACK_HEIGHT][TRACK_WIDTH]) {
    int x = 0, y = 0; // Começa no canto superior esquerdo
    int time = 0, penalty = 0, revisited = 0;
    int visited[TRACK_HEIGHT][TRACK_WIDTH];
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < COMMANDS_LENGTH; i++) {
        if (track[y][x] == 'F') 
            break; // Se chegou no final

        // Marca a célula atual como visitada
        visited[y][x]++;
        if (visited[y][x] > 1) revisited++;

        // Executa o comando
        switch (ind->commands[i]) {
            case 0: // Baixo
                if (y < TRACK_HEIGHT - 1) y++;
                break;
            case 1: // Esquerda
                if (x > 0) x--;
                break;
            case 2: // Direita
                if (x < TRACK_WIDTH - 1) x++;
                break;
            default:
                // Caso de comando inválido, ignore ou penalize
                break;
        }

        // Checa obstáculos
        if (track[y][x] == 'X') penalty++;

        // Incrementa o tempo
        time++;
    }

    // Calcula distância Manhattan até a linha de chegada
    int distance = abs((TRACK_HEIGHT - 1) - y) + abs((TRACK_WIDTH - 1) - x);

    // Fator de distância normalizado (0.0 = longe, 1.0 = muito perto)
    float distanceFactor = ((float)(TRACK_HEIGHT + TRACK_WIDTH - distance)) / (TRACK_HEIGHT + TRACK_WIDTH);

    // Chama a função de fitness
    float fitness = calculateFitness(time, penalty + revisited, distanceFactor);
    return fitness;
}
