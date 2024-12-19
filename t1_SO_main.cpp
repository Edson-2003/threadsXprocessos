#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <chrono>

using namespace std;

#define average 100
#define iteration 10
#define radios_initial 1000

struct arg_t 
{
  int begin;
  int end;
  FILE *file;
};

void process(int pid, int begin, int end, FILE* file)
{
  double length, diameter;
  double radios = radios_initial + (begin * 10);
  double pi;

  for (int i = begin; i < end; i++, radios += 10)
  {
    length = 2 * M_PI * radios;
    diameter = 2 * radios;
    pi = length / diameter;

    if((i % 10000) == 0)
    {
      fprintf(file, "Processo: %d\tIteração: %d\tPi: %3.14lf\n", pid, i, pi); 
    }
  } 

  exit(0);
}

void*
thread(void* args)
{
  struct arg_t *t = (struct arg_t*) args;
  double pi = 0.0;
  double length, diameter;
  double radios = radios_initial + (t->begin * 10);

  for(int i = t->begin; i < t->end; i++, radios += 10)
  {
    length = 2 * M_PI * radios;
    diameter = 2 * radios;
    pi = length / diameter;    
    
    if((i % 10000) == 0)
    {
      fprintf(t->file, "Iteração: %d\tPi: %3.14lf\n", i, pi); 
    }
  }

  return 0;
}

int main()
{
  chrono::time_point<chrono::system_clock> start, end;
  chrono::duration<double> tmp_thread;
  chrono::duration<double> tmp_process;

  int aux = 0;
  int point_f;
   
  printf("________________________________________________________________\n");
  printf("|\tN\t|\tthread\t\t|\tprocesso\t|\n");
  printf("|_______________________________________________________________|\n");

  for(int i = 1; i <= iteration; i++)
  {  
    int interval = 1000000 / i;
    start = chrono::system_clock::now();
   
    for(int j = 0; j < average; j++)
    {
      FILE* file = fopen("threads.out", "wt");
      struct arg_t* arg = (struct arg_t*) malloc(i * sizeof(struct arg_t));
     
      pthread_t my_threads[i];
      
      for(int k = 0; k < i; k++)
      {
        arg[k].begin = (k * interval);
        arg[k].end = ((k+1)* interval);
        arg[k].file = file;

        pthread_create(&my_threads[k], NULL, &thread, (void *)&arg[k]);
      }
      for(int k = 0; k < i; k++)
      {
        pthread_join(my_threads[k], NULL);
      }
      
      fclose(file);
      free(arg);
    }

    end = chrono::system_clock::now();
    tmp_thread = (end - start) / average;
  
//================end_de_analise_da_thread=========================//
    
    start = chrono::system_clock::now();
    
    for(int j = 0; j < average; j++)
    {
      FILE* file = fopen("process.out", "wt");
      
      for(int k = 1; k <= i; k++)
      {
        pid_t pid = fork();
        
        if(pid == 0)
        {
          int begin = k * interval;
          int end = (k + 1) * interval;
        
          process(getpid(), begin, end, file);
        }

        if (pid < 0)
        {
          printf("Erro ao criar processo\n");
          exit(1);
        }
      }
      
      for (int k = 0; k < i; k++)
      {
        wait(NULL);
      }

      fclose(file);
    }

    end = chrono::system_clock::now();
    tmp_process = (end - start) / average;

    if((tmp_process > tmp_thread) && (aux == 0))
    {
      point_f = i;
      aux = 1;
    }

    printf("|\t%d\t|\t%3.5lf us\t|\t%3.5lf us\t|\n", i, ((tmp_thread.count())*1000000), ((tmp_process.count())*1000000));

  }
  printf("|_______________________________________________________________|\n");
  printf("|  Ponto de inflexao  |     %d                                     |\n", point_f);  
  printf("|_______________________________________________________________|\n");

  return 0;
}

