#include <mpi.h>
#include <stdio.h>

#define ROOT 0

int main(int argc, char *argv[]) {
  int rank, size, number;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == ROOT) {
    printf("Processo %d: Digite um número para transmitir: \n", rank);
    fflush(stdout);
    scanf("%d", &number); // Processo root lê o número do teclado
  }

  MPI_Bcast(&number, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
  printf("Processo %d recebeu o número: %d\n", rank, number);

  MPI_Finalize();

  return 0;
}

