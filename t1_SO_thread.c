#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <chrono>

#define num_threads 1
#define intervalo (1000000/num_threads)
#define raio_inicial 1000

using namespace std;

struct param_t 
{
  int inicio;
  int fim;
};

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
  start = chrono::system_clock::now();

  pthread_t minhas_threads[num_threads];
  struct param_t param[num_threads];
  
  for(int i = 0; i < num_threads; i++)
  {
    param[i].inicio = (i * intervalo);
    param[i].fim = ((i+1)* intervalo);
    pthread_create(&minhas_threads[i], NULL, &thread, (void *)&param[i]);
  }
 for(int i = 0; i < num_threads; i++)
  {
    pthread_join(minhas_threads[i], NULL);
  }
  
  end = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end - start;
    
  printf("%3.5lf us\n", ((elapsed_seconds.count())*1000000));    
  
  return 0;
}

