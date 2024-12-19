# threads e Processos
trabalho desenvolvido para a diociplina de Sistemas Operacionais, com o intuito de calcular o valor estimado do Pi e medir o tempo de calculo
para encontrar o ponto de inferencia

## Índice

- [threads e Processos](#threads-e-processos)
  - [Índice](#índice)
  - [Descrição do Projeto](#descrição-do-projeto)
  - [estruturas de dados do projeto](#estruturas-de-dados-do-projeto)
  - [Funções e seus usos](#funções-e-seus-usos)



## Descrição do Projeto

O projeto foi construido em C/C++, sendo tendo sua maioria de codigo base escrito em c e apenas a medição de tempo em c++.

## estruturas de dados do projeto

- **param_t**: estrutura que tem como objetivo armazenar o inicio e fim de intervalo de calculo para as funções

## Funções e seus usos

- **Fatorial**: Função utilizada apenas para gerar processamento e gasto de tempo durante a execução das threads e processos, assim forçando o CPU-Bound
- **Processo**: Função que define o codigo executado pelos processos criados, recebendo como parametro o pid do filho, o inicio de intervalo e o fim de intervalo
- **Thread**: Função que define o codigo que sera executado nas threads criadas, recebendo como parametro a estrutura **param_t** que delimita o intervalo de inicio e fim.


