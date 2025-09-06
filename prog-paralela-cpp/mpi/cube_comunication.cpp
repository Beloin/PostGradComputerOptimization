#include <cstdio>
#include <mpi.h>

int main (int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  printf("Hello from %d of %d\n", rank, size);

  // Form a line:
  // Communicate only with rank-1 && rank-2

  // Forma a cube:
  // 4
  // 1 ---- 4
  // |      |
  // |      |
  // 2 ---- 3
  //
  // 6
  //        1 ---- 6
  //       /|      |\
  //      / |      | \
  //     2------------5 // Can also be a different topology
  //      \ |      | /
  //       \|      |/
  //        3 ---- 4
  //
  // N
  //        1 ---------- N
  //        |            |
  //       ...          ...
  //        |            |
  //       N-x --------- N-x-1

  MPI_Finalize();
  return 0;
}
