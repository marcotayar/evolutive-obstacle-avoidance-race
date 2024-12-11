# Evolutive Obstacle Avoidance 

**Evolutive-race** é um projeto que implementa um sistema evolutivo para controlar um carrinho em uma pista, com o objetivo de melhorar a trajetória percorrida ao longo das gerações. A simulação é renderizada utilizando a biblioteca **SDL2**, e a cada 80 gerações, o melhor indivíduo da população é mostrado para análise visual.

## Funcionalidades

- **População**: Evolução de uma população de indivíduos, onde cada indivíduo é representado por uma sequência de comandos que controlam o movimento de um carrinho na pista.
 
- **Simulação Gráfica**: Visualização da trajetória tomada pelo carrinho utilizando SDL2.
 
- **Pista e Obstáculos**: A pista contém:
  - **S**: Ponto de início,
  - **F**: Ponto final,
  - **X**: Obstáculos.

- **Sistema Evolutivo**: Avaliação do "fitness" dos indivíduos, seleção, cruzamento e mutação para evoluir a população, onde cada indivíduo é avaliado com base na sua capacidade de navegar pela pista, evitando obstáculos e buscando o melhor caminho até o ponto de chegada (F).

## Estrutura de Arquivos

### `track.h`
Este arquivo contém a definição da pista e a simulação do movimento dos indivíduos. A pista é representada como uma matriz de caracteres com os seguintes símbolos:
- `S` - ponto de início.
- `F` - ponto de chegada.
- `X` - obstáculos.

Além disso, o arquivo define a estrutura de dados `Individual`, que contém os comandos para controlar o movimento do carrinho.

#### Funções:
- `createTrack()`: Cria a pista a partir de uma matriz fixa de caracteres.
- `printTrack()`: Imprime a pista no console.
- `simulateIndividual()`: Simula o movimento de um indivíduo na pista e calcula sua pontuação de fitness.

#### Estrutura de Dados:
- `Individual`: Define um indivíduo da população, com um vetor de comandos representando as direções a serem tomadas (0 = baixo, 1 = esquerda, 2 = direita). A estrutura também contém um valor de `fitness` que armazena a pontuação de desempenho do indivíduo.

### `population.h`
Este arquivo define a população de indivíduos e funções para manipulação da evolução genética. A população é uma estrutura que contém um array de indivíduos e métodos para inicializar, avaliar, evoluir, mutar, cruzar e ordenar os indivíduos com base no seu fitness.

#### Funções:
- `initializePopulation()`: Inicializa a população com comandos aleatórios.
- `evaluatePopulation()`: Avalia o fitness de todos os indivíduos na população.
- `evolvePopulation()`: Evolui a população para a próxima geração com seleção, cruzamento e mutação.
- `tournamentSelection()`: Realiza a seleção por torneio.
- `crossover()`: Realiza o cruzamento entre dois pais para gerar um descendente.
- `mutate()`: Realiza a mutação de um indivíduo.
- `sortPopulationByFitness()`: Ordena a população por fitness.

#### Estrutura de Dados:
- `Population`: Define a população de indivíduos, contendo um array de `Individual`s e estatísticas de fitness (média, melhor e pior fitness).

#### Constantes:
- `POPULATION_SIZE`: Número de indivíduos na população (3000).
- `TOURNAMENT_SIZE`: Número de indivíduos na seleção por torneio (30).
- `COMMANDS_LENGTH`: Número de comandos por indivíduo (200).
- `TRACK_WIDTH` e `TRACK_HEIGHT`: Dimensões da pista (100x100).

## Algoritmos Evolutivos

O algoritmo segue o ciclo clássico de algoritmos genéticos:

1. **Inicialização**: A população começa com indivíduos gerados aleatoriamente.
2. **Avaliação**: Cada indivíduo é avaliado de acordo com o seu desempenho na pista.
3. **Seleção**: Indivíduos são selecionados para reprodução através de torneios.
4. **Cruzamento**: Dois indivíduos selecionados cruzam seus comandos para gerar um novo descendente.
5. **Mutação**: O descendente sofre mutação com uma taxa de 2%.
6. **Substituição**: A população é substituída pela nova geração.
7. **Genocídio**: Se a população fica estagnada em um mesmo resultado, durante 100 gerações e sem encontrar o ponto final, a população é reinicializada, ou seja, todos os indivíduos são substituidos por novos gerados aleatoriamente.

Este processo é repetido por várias gerações até que uma solução satisfatória seja alcançada.

## Pré-requisitos

Antes de executar o projeto, certifique-se de que o **SDL2** esteja instalado em seu sistema.

### Instalação do SDL2 (Ubuntu)

Para instalar o SDL2 no Ubuntu, execute o seguinte comando:

```bash
sudo apt-get install libsdl2-dev


