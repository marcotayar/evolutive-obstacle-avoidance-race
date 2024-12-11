#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/track.h"
#include "headers/population.h"
#include "headers/fitness.h"

#define CELL_SIZE 10
#define FPS 90

// Definição de cores em RGB
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF

// Função para desenhar uma célula na interface gráfica
static void drawCell(SDL_Renderer *renderer, int x, int y, int color) {
    SDL_SetRenderDrawColor(renderer, 
        (color >> 16) & 0xFF, 
        (color >> 8) & 0xFF, 
        color & 0xFF, 
        255);
    SDL_Rect rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_RenderFillRect(renderer, &rect);
}

// Função para renderizar toda a pista
static void renderTrack(SDL_Renderer *renderer, char track[TRACK_HEIGHT][TRACK_WIDTH]) {
    for (int yy = 0; yy < TRACK_HEIGHT; yy++) {
        for (int xx = 0; xx < TRACK_WIDTH; xx++) {
            int color = WHITE;
            if (track[yy][xx] == 'X') color = RED;         // Obstáculo
            else if (track[yy][xx] == 'S') color = GREEN; // Ponto inicial
            else if (track[yy][xx] == 'F') color = BLUE;  // Ponto final
            drawCell(renderer, xx, yy, color);
        }
    }
}

// Função para simular graficamente o melhor indivíduo da população
static void simulateAndRender(SDL_Renderer *renderer, char track[TRACK_HEIGHT][TRACK_WIDTH], Individual *ind, int generation) {
    int x = 0, y = 0; 
    int timeSteps = 0;
    int collisions = 0;
    int cima = 0;

    printf("=== Simulação da Geração %d ===\n", generation);
    printf("Fitness do Melhor Indivíduo: %.2f\n", ind->fitness);
    printf("Comandos Executados:\n");

    for (int i = 0; i < COMMANDS_LENGTH; i++) {
        printf("Passo %d: Comando=%d (Posição: x=%d, y=%d)\n", i, ind->commands[i], x, y);

        // Renderização da cena
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderTrack(renderer, track);
        drawCell(renderer, x, y, GREEN); // Carrinho
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);

        // Verifica se atingiu o final
        if (track[y][x] == 'F') {
            printf("Carrinho chegou ao final da pista na geração %d!\n", generation);
            break;
        }

        // Executa o comando do indivíduo
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
            case 3: //Cima
                if (y > 0) {
                    y--;
                    cima ++;
                    }
                break;
            default:
                // Caso de comando inválido, ignore ou penalize
                break;
        }

        // Verifica colisão com obstáculo
        if (track[y][x] == 'X') {
            collisions++;
            printf("Colisão detectada na posição x=%d, y=%d no passo %d.\n", x, y, i + 1);
            break;
        }

        timeSteps++;
    }

    printf("Posição Final do Carrinho: x=%d, y=%d\n", x, y);
    printf("Número de Colisões: %d\n", collisions);
    printf("Tempo Total de Simulação (steps): %d\n", timeSteps);
    printf("Fim da Simulação para Geração %d\n\n", generation);
}

int main(void) {
    srand((unsigned int)time(NULL)); // Semente aleatória

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Simulação do Carrinho",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        TRACK_WIDTH * CELL_SIZE, TRACK_HEIGHT * CELL_SIZE,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erro ao criar renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    char track[TRACK_HEIGHT][TRACK_WIDTH];
    Population population;

    createTrack(track);
    initializePopulation(&population);

    for (int generation = 0; generation < 400; generation++) {
        evaluatePopulation(&population, track);
        
        // Ordenar a população por fitness após avaliar
        sortPopulationByFitness(&population);

        // Imprimir estatísticas
        printFitnessStats(&population, generation);

        // Simular melhor indivíduo a cada 80 gerações
        if (generation % 80 == 0) {
            simulateAndRender(renderer, track, &population.individuals[0], generation);
        }

        // Evoluir população
        evolvePopulation(&population, track);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
