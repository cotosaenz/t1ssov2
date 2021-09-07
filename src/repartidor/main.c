#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../file_manager/manager.h"

int main(int argc, char const *argv[])
{

  int sem_1;
  int sem_2;
  int sem_3;

  void signal_handlr(int signal, siginfo_t *info_signal, void *ucontext)
  {
    int valor = info_signal->si_value.sival_int;
    printf("Llego senal a repartidor %d y DICE %d\n", getpid(), valor);
    int num_semaforo = (int) valor/10;
    int color = valor - (num_semaforo*10);
    printf("SEM %i color %i\n", num_semaforo, color);
    if (num_semaforo == 1)
    {
      sem_1 = color;
    }
    else if (num_semaforo == 2)
    {
      sem_2 = color;
    }
    else if (num_semaforo == 3)
    {
      sem_3 = color;
    }
  }

  connect_sigaction(SIGUSR1, signal_handlr);

  int n = atoi(argv[1]);
  int ds1 = atoi(argv[2]);
  int ds2 = atoi(argv[3]);
  int ds3 = atoi(argv[4]);
  int db = atoi(argv[5]);
  int pos = 0;
  int tiempo1 = 0;
  int tiempo2 = 0;
  int tiempo3 = 0;
  int tiempob = 0;  
  int avanza = 1;
  printf("Repartidor numero %i creado con id %d\n", n, getpid());

  while (avanza == 1)
  {
    if (pos == ds1 - 1)
    {
      tiempo1 = pos;
      if (sem_1 == 1)
      {
        pos += 1;
      }
    }
    else if (pos == ds2 - 1)
    {
      tiempo2 = pos;
      if (sem_2 == 1)
      {
        pos += 1;
      }
    }
    else if (pos == ds3 - 1)
    {
      tiempo3 = pos;
      if (sem_3 == 1)
      {
        pos += 1;
      }
    }
    else if (pos == db)
    {
      tiempob = pos;
      avanza = 0;
      printf("REPARTIDOOOOOOOOOOOOOOOOR %d\n", n);
      printf("tiempo 1: %i pid: %i\n", tiempo1, getpid());
      printf("tiempo 2: %i pid: %i\n", tiempo2, getpid());
      printf("tiempo 3: %i pid: %i\n", tiempo3, getpid());
      printf("tiempo b: %i\n", tiempob);
      exit(0);
    }
    else{
      pos += 1;
    }
    sleep(1);
    printf("POS %i     sem1: %i, sem2: %i, sem3: %i, bodega: %i\n", pos, sem_1, sem_2, sem_3, db);
  }
}
