# Evolutive-race

**Evolutive-race** é um projeto que implementa um sistema evolutivo para controlar um carrinho em uma pista, com o objetivo de melhorar a trajetória percorrida ao longo das gerações. A simulação é renderizada utilizando a biblioteca **SDL2**, e a cada 80 gerações, o melhor indivíduo da população é mostrado para análise visual.

## Funcionalidades

- **Evolução de População**: A cada geração, a população de indivíduos é avaliada com base em seu desempenho na pista. Cada indivíduo é representado por uma sequência de comandos que controlam o movimento do carrinho.
  
- **Simulação Gráfica**: A simulação é visualizada em tempo real, exibindo a trajetória do carrinho na pista, incluindo pontos de início, fim e obstáculos, através da renderização com SDL2.

- **Pista e Obstáculos**: A pista contém:
  - **S**: Ponto de início,
  - **F**: Ponto final,
  - **X**: Obstáculos.

- **Algoritmos Genéticos**: Utiliza técnicas de evolução como seleção, cruzamento e mutação para aprimorar a população a cada geração, baseando-se no "fitness" (aptidão) dos indivíduos.

## Tecnologias Utilizadas

- **Linguagem**: C
- **Biblioteca Gráfica**: SDL2
- **Estrutura de Dados**: Vetores e Matrizes
- **Algoritmo Evolutivo**: Algoritmos genéticos (seleção, cruzamento e mutação)
  
## Pré-requisitos

Antes de executar o projeto, certifique-se de que o **SDL2** esteja instalado em seu sistema.

### Instalação do SDL2 (Ubuntu)

Para instalar o SDL2 no Ubuntu, execute o seguinte comando:

```bash
sudo apt-get install libsdl2-dev
