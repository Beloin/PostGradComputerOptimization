#include "omp.h"
#include <functional>
#include <iomanip>
#include <iostream>

int main(int argc, char *argv[]) {
  int nt, nc, mt;
  nt = nc = mt = 0;
  nt = omp_get_num_threads();
  nc = omp_get_num_procs();
  mt = omp_get_max_threads();

  std::cout << "Default N° Threads: " << nt << "\n"
            << "Procesors: " << nc << "\nMax Threads: " << mt << std::endl
            << std::endl;

  double timea = omp_get_wtime();
  for (int i = 0; i < 100000000; i++) {
    i++;
    i--;
  }
  double timeb = omp_get_wtime();

  double tick = omp_get_wtick();

  int devnum = omp_get_device_num();
  std::cout << "N° Devices: " << devnum << "\n"
            << "Resolution: " << std::setprecision(10) << tick << "\n"
            << "Time Passed: " << timeb - timea
            << "\n"
            // << "Procesors: " << nc << "\nMax Threads: " << mt << std::endl
            << std::endl;
  return 0;
}
