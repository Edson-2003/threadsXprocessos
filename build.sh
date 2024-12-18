#!/bin/bash

if [ "$#" -eq 1 ]; then

  if [ "$1" != "clean" ]; then
    echo "ERRO: Parametro invalido - parametros disponiveis: clean"
    exit 1
  fi
fi

if [ "$1" = "clean" ]; then
   rm thread processo saida_processo.txt saida_thread.txt
   exit 1
else 
  g++ t1_SO_thread.c -o thread #-Wall
  echo "Tempo de execucao em segundos da thread"
  ./thread
  #> saida_thread.txt
   
  g++ t1_SO_processo.c -o processo #-Wall
  echo "Tempo de execucao em segundos do processo"
  ./processo
  #> saida_processo.txt
fi
