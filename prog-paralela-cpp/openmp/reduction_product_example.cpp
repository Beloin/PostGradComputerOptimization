#include <omp.h>
#include <stdio.h>

#define N 1000000000000
#define NUM_THREADS 4

long long product_array(int array[], long size) {
  long product = 1; // Inicializar produto como 1 para multiplicaçao
  #pragma omp parallel for reduction(+ : product)
  for (int i = 0; i < size; i++) {
    product += array[i]; // Multiplicar cada elemento do array no produto
  }
  return product;
}


int main() {
  // High N makes core dump: /var/lib/systemd/coredump/core.reduction_examp.1000.bc76049f4cf0405099ce04a0973ed185.182772.1755907078000000.zst
  int array[N];
  long long int product;
  // Inicializar array
  for (int i = 0; i < N; i++) {
    array[i] = i + 1; // Inicializar elementos do array com valores de 1 a N
  }
  // Chamar funçao paralelizada para calcular o produto
  double timea = omp_get_wtime();
  product = product_array(array, N);
  double timeb = omp_get_wtime();

  // Ordem de grandeza da saída! -> Aí é foda
  printf("Produto dos elementos do array: %lld\n", product);

  printf("Time spent (%d threads): %f\n", NUM_THREADS, timeb - timea);
  return 0;
}
