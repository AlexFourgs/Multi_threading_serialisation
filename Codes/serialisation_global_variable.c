#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

/**
    Variable globale pour les threads sérialisé
**/
int T=2;

/**
    déclaration des threads :
        * thread_concurrent correspond aux threads normaux
        * thread_serial correspond aux threads qui fonctionnent dans certaines conditions de sérialisation.
**/
static void *thread_concurrent (void *data){
  while(1){
    if (data != NULL){
      int* thread_number = (int*)data;
      printf("Thread T%d travail\n", *thread_number);
    }
    else {
      printf("Thread T? travail\n");
    }

    sleep(1);

  }
  return NULL ;
}


static void *thread_serial (void *data){

  while(1){
    if (data != NULL){
      int* thread_number = (int*)data ;

      if(*thread_number == T){ // C'est au tour du thread actuel de travailler
        printf("Thread T%d travail\n", *thread_number);
        sleep(1);
        //break;

        if(T == 4){ // Dernier thread serial, on le remet à 2
            T = 2 ;
        }
        else {
          T = T+1 ;
        }
      }
    }
  }

  return NULL ;
}


int main (int argc, char* argv[]){
  pthread_t t1, t2, t3, t4, t5 ;
  int one, two, three, four, five;

  one = 1 ;
  two = 2 ;
  three = 3 ;
  four = 4 ;
  five = 5 ;

  printf("Début simulation\n");

  pthread_create(&t1, NULL, thread_concurrent, &one);
  pthread_create(&t2, NULL, thread_serial, &two);
  pthread_create(&t3, NULL, thread_serial, &three);
  pthread_create(&t4, NULL, thread_serial, &four);
  pthread_create(&t5, NULL, thread_concurrent, &five);

  while(1){
    pthread_join(t1 ,NULL);
    pthread_join(t2 ,NULL);
    pthread_join(t3 ,NULL);
    pthread_join(t4 ,NULL);
    pthread_join(t5 ,NULL);
  }

  printf("Fin simulation\n");
  return 0 ;
}
