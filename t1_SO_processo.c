#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define intervalo (1000000 / 5)
#define raio_inicial 1000

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
      printf("PID: %d Incremento %d PI: %.10lf\n", pid, i, pi_estimado);
    }
  }

  exit(0);
}

int main()
{
  for (int i = 0; i < 5; i++)
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
  
  return 0;
}
