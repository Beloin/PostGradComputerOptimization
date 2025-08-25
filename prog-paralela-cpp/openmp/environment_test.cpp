#include "omp.h"
#include <stdio.h>

int main (int argc, char *argv[]) {
  int numThreadsOuter, numThreadsInner;

  // Empyrical tests must be made to check it
  omp_set_nested(1); // Nested make parallel region inside parallel region
  omp_set_dynamic(1);

  #pragma omp parallel private(numThreadsOuter)  num_threads(4)
  {
    numThreadsOuter = omp_get_num_threads();

    #pragma omp barrier
    printf("External parallel region with %d threads\n", numThreadsOuter);

    #pragma omp parallel private(numThreadsInner) num_threads(2)
    {
      numThreadsInner = omp_get_num_threads();

      #pragma omp barrier
      printf("\tInternal parallel region with %d threads\n", numThreadsInner);
    }
  }

  return 0;
}
