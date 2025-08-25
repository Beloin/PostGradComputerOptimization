#include <omp.h>
#include <random>
#include "iostream"

using namespace std::literals;

int main(int argc, char *argv[])
{
  std::cout << "Hello\n";;

  int numThreads = 5;
  omp_set_num_threads(numThreads);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);
  gen.seed(12);
  
  int n = 12;
  int array[n];
  
  #pragma omp parallel for
  for (int i = 0; i<n; i++) {
    // array[i] = dis(gen); // Cannot do this, generators are NOT thread safe
    array[i] = i*i;

    #pragma omp critial
    {
      std::cout << "Thread " << omp_get_thread_num() << " Got " << array[i] << std::endl;
    }
  }

  int sum =0;
  #pragma omp parallel for reduction(+:sum)
  for (int i=0; i <n; i++) {
    sum +=array[i];
  }

  std::cout << "Sum: " << sum << std::endl;

  return EXIT_SUCCESS;
}
