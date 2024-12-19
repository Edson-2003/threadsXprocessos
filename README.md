# Threads e Processos
Projeto desenvolvido para a diociplina de Sistemas Operacionais, com o intuito de calcular o valor estimado do Pi e medir o tempo de calculo
para encontrar o ponto de inferencia.

## Índice

- [Threads e Processos](#threads-e-processos)
  - [Índice](#índice)
  - [Descrição do Projeto](#descrição-do-projeto)
  - [Estruturas de dados do projeto](#Estruturas-de-dados-do-projeto)
  - [Funções e seus usos](#funções-e-seus-usos)
  - [Falando sobre a Main](#falando-sobre-a-main)
  - [Integrantes do Grupo](#integrantes-do-grupo)



## Descrição do Projeto

O projeto foi construido em C/C++, tendo sua maioria de codigo base escrito em c e apenas a medição de tempo em c++ utilizando a biblioteca chrono.

## Estruturas de dados do projeto

- **arg_t**: estrutura que tem como objetivo armazenar o inicio e fim de intervalo de calculo para as funções e o ponteiro do arquivo de I/O.

## Funções e seus usos

- **Processo**: Função que define o codigo executado pelos processos criados, recebendo como parametro o pid do filho, o inicio de intervalo, o fim de intervalo e o ponteiro do arquivo.
- **Thread**: Função que define o codigo que sera executado nas threads criadas, recebendo como parametro a estrutura **arg_t** que delimita o intervalo de inicio, fim e o ponteiro do arquivo.

## Falando sobre a Main
Em nossa função main acontece o gerenciamento do comportamento de cada thread e de cada processo, e também fazendo a media da medição de tempo para a execução com N threads e N processos.

## Integrantes do Grupo
- Edson Augusto Pereira Ferreira
- Gustavo Oliveira da Silva
- Lucas Robiati Sant'Ana
