#include <stdio.h>
#include <unistd.h>
#include "../file_manager/manager.h"
#include <stdlib.h>

int main(int argc, char const *argv[])
{
 
  int sigo = 1;
  void signal_handler(int signal, siginfo_t *info_signal, void *ucontext)
  {
    printf("voy a terminar\n");
    sigo = 0;
  }

  int cambios = -1;
  connect_sigaction(SIGUSR1, signal_handler);
  int delay = atoi(argv[1]);
  int pid_fabrica = atoi(argv[2]);
  int id_semaforo = atoi(argv[3]);
  int rojo = 0;
  int verde = 1;
  printf("I'm the SEMAFORO process and my PID is: %i y el PID de mi papá es: %d y mi delay es: %d y el PID del proceso fábrica es: %d y el id del semaforo es: %d\n", getpid(), getppid(), delay, pid_fabrica, id_semaforo);
  while (sigo == 1){
    sleep(delay);
    printf("semaforo %d mando %d\n", id_semaforo, (id_semaforo*10)+verde);             // si termina en 0 (10,20 o 30), cambia a rojo
    send_signal_with_int(pid_fabrica, (id_semaforo*10)+verde);    // si termina en 1 (11,21 o 31), cambia a verde
    cambios += 1;
    printf("sigo = %d\n", sigo);
    sleep(delay);
    printf("semaforo %d mando %d\n", id_semaforo, (id_semaforo*10)+rojo);  
    send_signal_with_int(pid_fabrica, (id_semaforo*10)+rojo);
    cambios += 1;
  }


  printf("semaforo %i cambios totales = %i\n",id_semaforo, cambios);
}
