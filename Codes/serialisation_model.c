#include <time.h>
#include "thread_function.c"

/**
    Variable globale pour les threads sérialisé
**/
int T=2;


int main (int argc, char* argv[]){
  /**pthread_t t1, t2, t3, t4, t5 ;
  int two, three, four;

  two = 2 ;
  three = 3 ;
  four = 4 ;
  **/
  printf("Début simulation\n");

  read_model((char*)"model.txt", (char*)"r");

  
  /*pthread_create(&t1, NULL, thread_concurrent, NULL);
  pthread_create(&t2, NULL, thread_serial, &two);
  pthread_create(&t3, NULL, thread_serial, &three);
  pthread_create(&t4, NULL, thread_serial, &four);
  pthread_create(&t5, NULL, thread_concurrent, NULL);

  while(1){
    pthread_join(t1 ,NULL);
    pthread_join(t2 ,NULL);
    pthread_join(t3 ,NULL);
    pthread_join(t4 ,NULL);
    pthread_join(t5 ,NULL);
  }
  */
  printf("Fin simulation\n");
  return 0 ;
}
