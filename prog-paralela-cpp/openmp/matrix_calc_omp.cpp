#include <stdio.h>
#include <omp.h>

#define N 1000

int main(int argc, char *argv[]) {
  // TODO: Use random generator
  int A[N][N], B[N][N], C[N][N];
  int i, j, k;
  // Initialize matrices A and B
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      A[i][j] = i + j;
      B[i][j] = i - j;
    }
  }

  #pragma omp parallel for private(i, j, k) shared(A, B, C) num_threads(4)
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      C[i][j] = 0;

      // Nested parallelism for computing each element of
      // the result matrix C
      #pragma omp parallel for reduction(+:C[i][j])
      for (k = 0; k < N; k++) { // TODO: Change J for K to prevent cache misses
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  // for (int i = 0; i < N; i++) {
  //   for (int k = 0; k < N; k++) {
  //     C[i][j] = 0;
  //     for (int j = 0; j < N; j++) {
  //       C[i][j] += A[i][k] * B[k][j];
  //     }
  //   }
  // }

  int error = 0;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      int sum = 0;
      for (k = 0; k < N; k++) {
        sum += A[i][k] * B[k][j];
      }
      if (C[i][j] != sum) {
        error = 1;
        break;
      }
    }
    if (error)
      break;
  }
  if (error) {
    printf("Error: Matrix multiplication result is incorrect!\n");
  } else {
    printf("Matrix multiplication completed successfully.\n");
  }

  return 0;
}
