#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct element_thread element_thread; // Un élément qui contient un thread dans une liste chaînée et l'élément suivant.
typedef struct thread_c thread_c ;
typedef struct line line ; // Un élément qui contient le numéro de la ligne et un pointeur vers la liste chaînée de threads correspondant.

struct element_thread{
  char* thread_number ;
  pthread_t thread ;
  struct element_thread *next ;
};

typedef element_thread* thread_list ;

struct line{
  int line ;
  thread_list thread_line ;
  struct line *next ;
};

typedef line* line_list ;

thread_list addTop(thread_list list, char* thread_number){
  element_thread* newElement = (element_thread*)malloc(sizeof(element_thread));

  newElement->thread_number = thread_number ;
  newElement->next = list ;

  return newElement ;
}

thread_list addLast(thread_list list, char* thread_number){
  element_thread* newElement = (element_thread*)malloc(sizeof(element_thread));

  newElement->thread_number = thread_number ;
  newElement->next = NULL ;

  if (list == NULL){
    return newElement ;
  }
  else {
    element_thread* actual = list ;
    while(actual->next != NULL){
      actual = actual->next;
    }
    actual->next = newElement ;
    return list ;
  }
}

void printf_thread_list(thread_list list){
  element_thread* actual = list ;

  while(actual != NULL){
    printf("%s -> ", actual->thread_number);
    actual = actual->next ;
  }
  printf("End\n");
}


line_list addLast_line_list(line_list list, int nb_line, thread_list threads_list){
  line* newElement = (line*)malloc(sizeof(line));

  newElement->line = nb_line ;
  newElement->thread_line = threads_list;
  newElement->next = NULL ;

  if (list == NULL){
    return newElement ;
  }
  else {
    line* actual = list ;
    while(actual->next != NULL){
      actual = actual->next;
    }
    actual->next = newElement ;
    return list ;
  }
}


void printf_line_list(line_list list){
  line* actual = list ;

  while(actual != NULL){
    printf("LINE %d : ", actual->line);
    printf_thread_list(actual->thread_line);
    actual = actual->next ;
  }
}

int lenght_line_list(line_list list){
  int lenght = 0 ;

  while(list->next != NULL){
    lenght++ ;
    list = list->next ;
  }

  return lenght ;
}

/**
                                  ***FONCTIONS DE PARSING***
**/
void parse_model(FILE* file){
  char line[1000] = "" ;
  int counter = 0 ;
  line_list line_list_threads = NULL ;

  while(fgets(line, 100, file) != NULL){
    if(counter != 0){
      thread_list actual_line_list_threads = NULL ;

      // strtok par rapport à ":"
      char* token ;
      char* token2 ;
      int counter_thread = 0 ;

      // On récupère seulement ce qu'il y a après "LINE X :"
      token = strtok(line, ":");
      token = strtok(NULL, ":");

      // On récupère ce qu'il y a entre les flèches.
      token2 = strtok(token, "->");

      while((token2 != NULL) && (strcmp(token2, " End\n"))){
        counter_thread++ ;

        printf("token2 : %s\n", token2);
        actual_line_list_threads = addLast(actual_line_list_threads, token2);
        
        token2 = strtok(NULL, "->");
      }
      printf("J'ajoute :\n");
      printf_thread_list(actual_line_list_threads);
      printf("À la liste de ligne.\n");
      line_list_threads = addLast_line_list(line_list_threads, counter, actual_line_list_threads); // On ajoute la ligne de threads dans la liste des lignes.

      printf("Liste de ligne :\n");
      printf_line_list(line_list_threads);
      printf("\n\n");

    }
    counter++ ;
    //printf_line_list(line_list_threads);
  }
}

/**
    Fonction qui ouvre un fichier et fait appel à la fonction de parsing.
**/
void read_model(char* fileName, char* openMode){
  FILE* model = NULL ; // Pointeur sur le fichier correspondant au modèle.
  model = fopen(fileName, openMode);
  int nb_thread_c = 0 ;

  if (model != NULL){
    // On récupère le nombre de ligne(s) de thread(s)
    fscanf(model, "NB_LINES = %d", &nb_thread_c);

    printf("Nb thread concurrent = %d\n", nb_thread_c);

    parse_model(model);

    fclose(model);
  }
  else {
    printf("Error while opening file %s", fileName);
  }
}

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
  int T = 0 ;

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

int lenght_list(thread_list list){
  int lenght = 0 ;

  while(list->next != NULL){
    lenght++ ;
    list = list->next ;
  }

  return lenght ;
}
