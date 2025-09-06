#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3 // Tamanho das matrizes (3x3)

void read_matrix(int matrix[N][N], const char *name) {
  printf("Digite os elementos da matriz %s (3x3):\n", name);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      scanf("%d", &matrix[i][j]);
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
    for (int k = 0; k < N; k++)
      result[j] += line_A[k] * B[k][j];
  }
}

int main(int argc, char *argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int A[N][N], B[N][N], *C = NULL;
  int line_A[N]; // Linha que cada processo receberá
  int result[N]; // Resultado local de cada processo

  if (rank == 0) {
    // Leitura das matrizes no processo root
    read_matrix(A, "A");
    read_matrix(B, "B");
    C = (int*)malloc(N * N * sizeof(int)); // Aloca espaço para a matriz resultante
  }

  // Distribui as linhas da matriz A entre os processos
  MPI_Scatter(A, N, MPI_INT, line_A, N, MPI_INT, 0, MPI_COMM_WORLD);

  // Envia a matriz B completa para todos os processos
  MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);

  // Cada processo calcula a linha correspondente da matriz C
  mult_line(line_A, B, result);

  // Coleta as linhas calculadas no processo root
  MPI_Gather(result, N, MPI_INT, C, N, MPI_INT, 0, MPI_COMM_WORLD);

  // O processo root imprime a matriz resultante
  if (rank == 0) {
    print_matrix(C);
    free(C); // Libera a memória alocada
  }

  MPI_Finalize();
  return 0;
}
