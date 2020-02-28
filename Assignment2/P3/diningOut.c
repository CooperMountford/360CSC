#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5 // number of philosophers

typedef struct {
  int p_num; // our assigned thread number (position at table)
} phil_info;

void *thread_start(void *arg);

sem_t lock;
sem_t chopsticks[N];
pthread_t philosophers[N];

int main() {

  // init
  for (int i = 0; i < N; i++) {
    sem_init(&chopsticks[i], 0, 1);
  }

  sem_init(&lock, 0, 2);

  for (int i = 0; i < N; i++) {
    phil_info *arg = malloc(sizeof(phil_info));
    arg->p_num = i;

    pthread_create(&philosophers[i], NULL, thread_start, (void *)arg);
  }

  for (int i = 0; i < N; i++)
    pthread_join(philosophers[i], NULL);
}

void think(int num) {
   printf("Philosopher %d is thinking\n", num);
}

void eat(int num) {
   printf("Philosopher %d is eating with forks %d and %d\n", num, (num+1)%5, num);
}

void *thread_start(void *arg) {
  phil_info self = *(phil_info *)arg;

  while (1) {
    think(self.p_num);
    sem_wait(&lock);
    sem_wait(&chopsticks[self.p_num]);
    sem_wait(&chopsticks[(self.p_num + 1) % 5]);
    sleep(1);
    eat(self.p_num);
    sem_post(&chopsticks[self.p_num]);
    sem_post(&chopsticks[(self.p_num + 1) % 5]);
    sem_post(&lock);
    sleep(0);
  }
  return 0;
}