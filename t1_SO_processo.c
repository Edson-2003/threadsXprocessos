#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <time.h>
#include <chrono>

using namespace std;

#define num_processos 1
#define intervalo (1000000 / num_processos)
#define raio_inicial 1000

double fatorial(int n)
{
  double vfat;
  
  if ( n <= 1 )
    //Caso base: fatorial de n <= 1 retorna 1
    return (1);
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
    
    if((i %10000) == 0)
    {
      //printf("PID: %d Incremento %d PI: %.10lf\n", pid, i, pi_estimado);
    }
  }

  double f = fatorial(20); 

  //printf("%lf\n", f);

  exit(0);
}

int main()
{
  chrono::time_point<chrono::system_clock> start, end;
  start = chrono::system_clock::now();

  for (int i = 0; i < num_processos; i++)
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
      //printf("Erro ao criar processo\n");
      exit(1);
    }
  }

  for(int i = 0; i < num_processos; i++)
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
  chrono::duration<double> elapsed_seconds = end - start;

  printf("%3.5lf us\n", ((elapsed_seconds.count())*1000000));    

  return 0;
}
