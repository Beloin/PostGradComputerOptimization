
#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// This requires that: -np == 4
#define N 3 // Tamanho das matrizes (3x3)

void read_matrix(int matrix[N][N], const char *name) {
  printf("Digite os elementos da matriz %s (3x3):\n", name);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
#pragma omp parallel sections
      {
#pragma omp section
        {
          scanf("%d", &matrix[i][j]);
        }

#pragma omp section
        {
          char s[3];
          sprintf(s, "%d\n", i + j);
          write(STDIN_FILENO, s, 3);
        }
      }
    }
  }
}

void print_matrix(int *matrix) {
  printf("Matriz resultante:\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%3d ", matrix[i * N + j]);
    }
    printf("\n");
  }
}

void mult_line(int line_A[N], int B[N][N], int result[N]) {
  for (int j = 0; j < N; j++) {
    result[j] = 0;
    for (int k = 0; k < N; k++) {
      result[j] += line_A[k] * B[k][j];
    }
  }
}

int main(int argc, char *argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int A[N][N], B[N][N], *C = NULL;
  int result[N]; // Linha da matriz C que o processo irá calcular

  if (rank == 0) {
    read_matrix(A, "A");
    read_matrix(B, "B");
    C = (int *)malloc(N * N * sizeof(int *));
  }

  MPI_Bcast(A, N * N, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);

  mult_line(A[rank], B, result);

  MPI_Gather(result, N, MPI_INT, C, N, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    print_matrix(C);
    free(C); // malloc == free
  }

  printf("End!\n");
  MPI_Finalize();
  return 0;
}
