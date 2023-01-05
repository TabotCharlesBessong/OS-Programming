#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

// Semaphores for chopsticks
sem_t chopsticks[NUM_PHILOSOPHERS];

// Function prototypes
void *philosopher(void *num);

int main() {
  int i;
  pthread_t philosophers[NUM_PHILOSOPHERS];

  // Initialize semaphores for chopsticks
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    sem_init(&chopsticks[i], 0, 1);
  }

  // Create threads for philosophers
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_create(&philosophers[i], NULL, philosopher, (void *)i);
  }

  // Wait for all threads to complete
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_join(philosophers[i], NULL);
  }

  return 0;
}

void *philosopher(void *num) {
  int i = (int)num;
  int left = i;
  int right = (i + 1) % NUM_PHILOSOPHERS;

  while (1) {
    // Think
    printf("Philosopher %d is thinking.\n", i);
    sleep(1);

    // Pick up chopsticks
    printf("Philosopher %d is trying to pick up chopsticks %d and %d.\n", i, left, right);
    sem_wait(&chopsticks[left]);
    sem_wait(&chopsticks[right]);

    // Eat
    printf("Philosopher %d is eating.\n", i);
    sleep(1);

    // Put down chopsticks
    sem_post(&chopsticks[left]);
    sem_post(&chopsticks[right]);
  }
}
