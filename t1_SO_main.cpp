#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <chrono>

using namespace std;

#define iteration 100
#define intervalo (1000000/10)
#define raio_inicial 1000

struct param_t 
{
  int inicio;
  int fim;
};

double fatorial(int n)
{
  double vfat;
  
  if ( n <= 1 )
  {
    //Caso base: fatorial de n <= 1 retorna 1
    return (1);
  }
  else
  {
    //Chamada recursiva
    vfat = n * fatorial(n - 1);
    return (vfat);
  }
}

void processo(int pid, int inicio, int fim)
{
  double comprimento, diametro;
  double raio = raio_inicial + (inicio * 10);
  double pi_estimado;

  for (int i = inicio; i < fim; i++, raio += 10)
  {
    comprimento = 2 * M_PI * raio;
    diametro = 2 * raio;
    pi_estimado = comprimento / diametro;
  } 
  double f = fatorial(20); 

  exit(0);
}

void*
thread(void* args)
{
  struct param_t *t = (struct param_t*) args;
  double pi_estimado = 0.0;
  double comprimento, diametro;
  double raio = raio_inicial + (t->inicio * 10);

  for(int i = t->inicio; i < t->fim; i++, raio += 10)
  {
    comprimento = 2 * M_PI * raio;
    diametro = 2 * raio;

    pi_estimado = comprimento / diametro;    
  }

  double f = fatorial(20);
  
  return 0;
}

int main()
{
  chrono::time_point<chrono::system_clock> start, end;
  chrono::duration<double> tmp_thread;
  chrono::duration<double> tmp_processo;

  int aux = 0;
  int ponto_f;
   
  printf("________________________________________________________________\n");
  printf("|\tN\t|\tthread\t\t|\tprocesso\t|\n");
  printf("|_______________________________________________________________|\n");

  for(int j = 1; j <= iteration; j++)
  {  
    start = chrono::system_clock::now();
    struct param_t param[j];
   
    pthread_t minhas_threads[j];
    
    for(int i = 0; i < j; i++)
    {
      param[i].inicio = (i * intervalo);
      param[i].fim = ((i+1)* intervalo);
      pthread_create(&minhas_threads[i], NULL, &thread, (void *)&param[i]);
    }
    for(int i = 0; i < j; i++)
    {
      pthread_join(minhas_threads[i], NULL);
    }
    
    end = chrono::system_clock::now();
    tmp_thread = end - start;
  
//================fim_de_analise_da_thread=========================//
    
    start = chrono::system_clock::now();
    
    for (int i = 1; i < j; i++)
    {
      pid_t pid = fork();
      
      if(pid == 0)
      {
        int inicio = i * intervalo;
        int fim = (i + 1) * intervalo;
      
        processo(getpid(), inicio, fim);
      }

      if (pid < 0)
      {
        printf("Erro ao criar processo\n");
        exit(1);
      }
    }

    for(int i = 0; i < j; i++)
    {
      int ret2, status2, s ;
          ret2 = wait(&status2) ;
          if ((status2&255) == 0) {
          }
          else {
            s = status2&255 ;
          }
    }
    end = chrono::system_clock::now();
    tmp_processo = end - start;

    if((tmp_processo > tmp_thread) && (aux == 0))
    {
      ponto_f = j;
      aux = 1;
    }

    printf("|\t%d\t|\t%3.5lf us\t|\t%3.5lf us\t|\n", j, ((tmp_thread.count())*1000000), ((tmp_processo.count())*1000000));

  }
  printf("|_______________________________________________________________|\n");
  printf("|  Ponto de flexao  |     %d                                     |\n", ponto_f);  
  printf("|_______________________________________________________________|\n");

  return 0;
}

