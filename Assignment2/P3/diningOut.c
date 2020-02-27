#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5 // number of philosophers

struct phil_info {
   pthread_t phil_id; // id from pthread_create
   int p_num; // our assigned thread number (position at table)

}



int main(int argc, char* argv[]) {
   sem_t lock;
   sem_t chopsticks[N];
   pthread_t philosophers[N];

   //init
   for(int i = 0; i < M; i++) {
     sem_init(&chopsticks[i], 0, 1);
   }

   sem_init(&lock, 0, 4);

   for (int i = 0; i < N; i++) {
      phil_info* arg = malloc(sizeof(phil_info));
      arg -> p_num = i;
      arg ->
   }


}


void* thread_start(void* arg) {
   struct phil_info* pinfo = arg;



}

void think(int num) {
   printf("Philosopher %d is thinking\n", num);
}

void eat(int num) {
   printf("Philosopher %d is eating\n", num);
}

































/*
int phil[5] = { 0, 1, 2, 3, 4 };

pinfo = malloc(sizeof(struct phil_info));

struct phil_info {
           int order;
           int       thread_num;
           char     *argv_string;
       };

int main(int argc, char *args[]) {
  sem_t lock;
  sem_t chopsticks[5];
  pthread_t philosophers[5];

  //init
  for(int i = 0; i < 5; i++) {
    sem_init(&chopsticks[i], 0, 1);
  }

  sem_init(&lock, 0, 4);

  //run
  for(int i = 0; i < 5; i++) {
     pthread_create(&philosophers[i], NULL, philosopher, (void*) args);
  }

  return 0;
}

void* philosopher(void* num) {
   for (int i = 0; i < 3) {

   }
}

void think(int num) {
   printf("Philosopher %d is thinking\n", num);
}

void eat(int num) {
   printf("Philosopher %d is eating\n", num);
}

*/