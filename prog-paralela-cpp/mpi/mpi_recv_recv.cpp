
#include <cstdio>
#include <cstring>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int rank, size;
  int source, dest;
  int tag = 0;
  char message[100];
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank != 0) {
    sprintf(message, "Greetings from process %d!", rank);
    dest = 0;
    MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    // MPI_Send(message, strlen(message) + 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
  } else {
    for (source = 1; source < size; source++) {
      MPI_Recv(message, 100, MPI_CHAR, source, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      // MPI_Recv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
      printf("%s\n", message);
    }
  }

  MPI_Finalize();
  return 0;
}
