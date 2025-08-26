#include <omp.h>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

using namespace std::literals;

#define N_VALUES 1000000

std::random_device rd;
// 2. Seed a Mersenne Twister engine (a good general-purpose PRNG)
std::mt19937 gen(0);
std::uniform_int_distribution<> distrib(1, N_VALUES);

void merge(int arr[], int i, int middle, int j) {
  int n = j - i;
  int tempArr[n];
  int index = 0;
  int ni = i, nm = middle;
  while (ni < middle && nm < j) {
    if (arr[ni] < arr[nm]) {
      tempArr[index++] = arr[ni++];
    } else {
      tempArr[index++] = arr[nm++];
    }
  }

  while (ni < middle) {
    tempArr[index++] = arr[ni++];
  }

  while (nm < j) {
    tempArr[index++] = arr[nm++];
  }

  int oldIndex = 0;
  for (index = i, oldIndex = 0; index < j; index++, oldIndex++) {
    arr[index] = tempArr[oldIndex];
  }
}

void mergeSort(int arr[], int i, int j) {
  if (j - i <= 1)
    return;

  int middle = (i + j) / 2;
  mergeSort(arr, i, middle);
  mergeSort(arr, middle, j);
  merge(arr, i, middle, j);
}

void mergeSortParallel(int arr[], int i, int j) {
  if (j - i <= 1)
    return;

  int middle = (i + j) / 2;
#pragma omp parallel sections
  {
#pragma omp section
    mergeSort(arr, i, middle);

#pragma omp section
    mergeSort(arr, middle, j);
  }

  merge(arr, i, middle, j);
}

const std::string generateString(int *arr, int len) {
  std::stringstream str;

  str << "[ ";
  for (int i = 0; i < len; i++) {
    str << arr[i] << " ";
  }
  str << "]";

  return str.str();
}

void randomData(int *arr, int sz) {
  for (int i = 0; i < sz; i++) {
    arr[i] = distrib(gen);
  }
}

int main(int argc, char *argv[]) {
  omp_set_num_threads(16);
  int arr[N_VALUES];
  randomData(arr, N_VALUES);

  clock_t begin = clock();
  mergeSort(arr, 0, N_VALUES);
  clock_t end = clock();

  // std::cout << "Res: " << generateString(arr, N_VALUES) << std::endl;
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Tempo de execuçao (sequencial): %f segundos\n", time_spent);

  double ompbegin = omp_get_wtime();
  mergeSort(arr, 0, N_VALUES);
  double ompend = omp_get_wtime();
  printf("Tempo de execuçao (paralela): %f segundos\n", ompend - ompbegin);
  return 0;
}
