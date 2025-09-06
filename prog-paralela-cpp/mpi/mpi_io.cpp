#include <cstdio>
#include <mpi.h>

#define N 3
#define IO_RANK 0

void read_matrix(int matrix[N][N], const char *name) {
  printf("Digite os elementos da matriz %s (3x3):\n", name);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      scanf("%d", &matrix[i][j]);
    }
  }
}

void print_matrix(int matrix[N][N]) {
  printf("Matriz resultante:\n");
  for (int i = 0; i < N; i++) {
    printf("| ");
    for (int j = 0; j < N; j++) {
      if (j + 1 == N) {
        printf("%d ", matrix[i][j]);
      } else
        printf("%d, ", matrix[i][j]);
    }
    printf("|");
    printf("\n");
  }
}
int main(int argc, char *argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Status status;

  int A[N][N], B[N][N], C[N][N];
  int row[N];

  if (rank == IO_RANK) {
    read_matrix(A, "A");
    read_matrix(B, "B");

    for (int i = 0; i < N; i++) {
      MPI_Send(A[i], N, MPI_INT, i + 1, 0, MPI_COMM_WORLD);

      // ARRAY IS SEQUENTIALY STORED IN MEMORY
      MPI_Send(B, N * N, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
    }

    for (int i = 0; i < N; i++) {
      MPI_Recv(C[i], N, MPI_INT, i + 1, 0, MPI_COMM_WORLD, &status);
    }

    print_matrix(C);
  } else {
    MPI_Recv(A[rank-1], N, MPI_INT, IO_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    // MPI_Recv(row, N, MPI_INT, IO_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    MPI_Recv(B, N * N, MPI_INT, IO_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    int result[N];
    for (int i = 0; i < N; i++) {
      result[i] = 0;
      for (int ii = 0; ii < N; ii++) {
        result[i] += A[rank-1][ii] * B[i][ii];
        // result[i] += row[ii] * B[i][ii];
      }
    }

    MPI_Send(result, N, MPI_INT, IO_RANK, 0, MPI_COMM_WORLD);
  }

  return MPI_Finalize();

  return 0;
}
