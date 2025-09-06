#include <omp.h>
#include <random>
#include <stdio.h>

#define NUM_REGIONS 10000
#define YEARS 5000

typedef struct {
  char nome[50];
  double temperaturas[YEARS];
} Region;


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(1, 100);

void calcular_medias_temperatura(Region regioes[NUM_REGIONS],
                                 double medias[NUM_REGIONS]) {
  int i, j;

#pragma omp parallel for shared(regioes, medias) private(i, j)
  for (i = 0; i < NUM_REGIONS; i++) {
    // A lock is not necessary bc we are not using any data outside the thread `i` context
    double soma = 0.0;
    for (j = 0; j < YEARS; j++) {
      soma += regioes[i].temperaturas[j];
    }
    medias[i] = soma / YEARS;
    // printf("Thread %d processou a região %d\n", omp_get_thread_num(), i);
  }
}

Region regioes[NUM_REGIONS];
double medias_temperatura[NUM_REGIONS];

int main() {
  gen.seed(12);

  // Inicialização dos dados (exemplo simplificado)
  for (int i = 0; i < NUM_REGIONS; i++) {
    sprintf(regioes[i].nome, "Região %d", i + 1);
    for (int j = 0; j < YEARS; j++) {
      regioes[i].temperaturas[j] =
          20.0 + (i % 10); // Valores fictícios de temperatura
    }
  }

  double t1 = omp_get_wtime();
  // Cálculo das médias de temperatura utilizando OpenMP
  calcular_medias_temperatura(regioes, medias_temperatura);
  double t2 = omp_get_wtime();

  // Exibir resultados
  for (int i = 0; i < NUM_REGIONS; i++) {
    printf("Média de temperatura da %s: %.2f\n", regioes[i].nome,
           medias_temperatura[i]);
  }
  
  double tick = omp_get_wtick();
  printf("Time spent: %.2f\n", (t2-t1));

  return 0;
}
