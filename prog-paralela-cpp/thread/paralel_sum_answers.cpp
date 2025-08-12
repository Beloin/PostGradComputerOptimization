#include <future>
#include <iostream>
#include <numeric> // Para std::accumulate
#include <random>
#include <vector>

// Funcao que calcula a soma de uma subfaixa do vetor
int partial_sum(const std::vector<int> &vec, int start, int end) {
  return std::accumulate(vec.begin() + start, vec.begin() + end, 0);
}

// Funcao que realiza o somatorio em multiplas etapas
int parallel_sum(std::vector<int> &vec) {
  int num_threads = 100;
  std::vector<int> results(num_threads);
  std::vector<std::future<int>> futures;

  // Fase 1: Computar a soma de 10 elementos por thread
  for (int i = 0; i < num_threads; ++i) {
    int start = i * 10;
    int end = start + 10;
    futures.push_back(std::async(std::launch::async, partial_sum,
                                 std::cref(vec), start, end));
  }

  // Aguardar todas as threads terminarem e armazenar os resultados
  for (int i = 0; i < num_threads; ++i)
    results[i] = futures[i].get();

  // Fase 2: Reduzir o numero de threads pela metade a cada etapa
  while (num_threads > 1) {
    num_threads /= 2;
    futures.clear(); // Limpar os futures para a proxima fase
    for (int i = 0; i < num_threads;
         ++i) { // Somar pares de resultados em threads paralelas
      futures.push_back(std::async(
          std::launch::async, [](int a, int b) { return a + b; },
          results[2 * i], results[2 * i + 1]));
    }

    // Aguardar as threads e atualizar o vetor de resultados
    for (int i = 0; i < num_threads; ++i)
      results[i] = futures[i].get();
  }
  return results[0]; // Retorna o resultado final
}

int main() {
  // Criar um vetor com 1000 posicoes e preenche-lo com numeros aleatorios
  std::vector<int> vec(1000);
  std::random_device rd;
  std::mt19937 gen(rd());
  gen.seed(1);
  std::uniform_int_distribution<> dis(1, 100);
  for (int &v : vec)
    v = dis(gen);

  int result = parallel_sum(vec); // Chamar a funcao que realiza a soma paralela
  std::cout << "A soma total dos elementos do vetor e: " << result << std::endl;
  return 0;
}
