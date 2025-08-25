#include <cstdio>
#include <omp.h>

#define NUM_TASKS 10

void compute_task(int task_id) {
  printf("Task %d is being executed by thread %d\n", task_id,
         omp_get_thread_num());

  // Simulate computation
  for (int i = 0; i < 100000000; i++) {
    // Do some work
  }

  printf("Task %d has been completed by thread %d\n", task_id,
         omp_get_thread_num());
}

int main(int argc, char *argv[]) {

  // #pragma omp parallel sections
  // {
  //   #pragma omp section
  //   {
  //     printf("Hello Session 1\n");
  //   }
  //
  //   #pragma omp section
  //   {
  //     printf("Hello Section 2\n");
  //   }
  // }
  // printf("Finalized!\n");

#pragma omp parallel
  {
#pragma omp single
    {
      for (int i = 0; i < NUM_TASKS; i++) {
#pragma omp task
        compute_task(i);
      }
    }

#pragma omp parallel sections
    {
#pragma omp section
      {
        printf("Hello Session 1\n");
      }

#pragma omp section
      {
        printf("Hello Section 2\n");
      }
    }
    printf("Finalized!\n");
  }
  printf("All tasks have been created and executed\n");

  return 0;
}
