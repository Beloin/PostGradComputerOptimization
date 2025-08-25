#include "omp.h"
#include <cstdio>

#define NUM_INC 100000
#define NUM_THREADS 4

int counter = 0;
omp_lock_t lock;
omp_lock_t plock;

int main(int argc, char *argv[]) {
  omp_init_lock(&lock);
  omp_init_lock(&plock);

#pragma omp parallel num_threads(NUM_THREADS)
  {
    int tid = omp_get_thread_num();

    for (int i = 0; i < NUM_INC; i++) {
      // omp_set_lock(&lock);

      counter++;

      // omp_unset_lock(&lock);
    }

    omp_set_lock(&plock);

    printf("Thread %d: Couter = %d\n", tid, counter);

    omp_unset_lock(&plock);
  }

  omp_destroy_lock(&lock);
  omp_destroy_lock(&plock);

  return 0;
}
