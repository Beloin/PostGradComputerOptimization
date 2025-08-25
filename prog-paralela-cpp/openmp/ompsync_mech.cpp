#include "omp.h"
#include <cstdio>
#include <iostream>

#define NUM_INC 100000
#define NUM_THREADS 4

int counter = 0;
omp_lock_t lock;

int main(int argc, char *argv[]) {
  omp_init_lock(&lock);

#pragma omp parallel num_threads(NUM_THREADS)
  {
    int tid = omp_get_thread_num();

    for (int i = 0; i < NUM_INC; i++) {
      // omp_set_lock(&lock);

      // Does not needs to use locks
      // #pragma omp critical (counter_adder)
      #pragma omp atomic
      counter++;

      // omp_unset_lock(&lock);
    }

#pragma omp barrier
    char s[255];
    sprintf(s, "Thread %d: Couter = %d\n", tid, counter);
// printf("Thread %d: Couter = %d\n", tid, counter);
#pragma omp single
    std::cout << s;
  }

  omp_destroy_lock(&lock);

  return 0;
}
