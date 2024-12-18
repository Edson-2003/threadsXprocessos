#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define intervalo (1000000/5)
#define raio_inicial 1000

pthread_t minhas_threads[5];

struct param_t 
{
  int inicio;
  int fim;
};

void
thread(struct param_t *t)
{
  double pi_estimado = 0.0;
  double comprimento, diametro;
  double raio = raio_inicial + (t->inicio * 10);

  for(int i = t->inicio; i < t->fim; i++, raio += 10)
  {
    comprimento = 2 * M_PI * raio;
    diametro = 2 * raio;

    pi_estimado = comprimento / diametro;    
    
    if(i%10000 == 0)
    {
      printf("%d = %lf\n", i, pi_estimado);
    }
  }
}

int main()
{
  struct param_t param[5];
  
  for(int i = 0; i < 5; i++)
  {
    param[i].inicio = (i * intervalo);
    param[i].fim = ((i+1)* intervalo);
    pthread_create(&minhas_threads[i], NULL, (void *)thread, (void *)&param[i]);
  }
 for(int i = 0; i < 5; i++)
  {
    pthread_join(minhas_threads[i], NULL);
  }
  
  return 0;
}

