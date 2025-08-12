#include <functional>
#include <future>
#include <iostream>
#include <numeric>
#include <ostream>
#include <random>
#include <vector>

int partial_sum(const std::vector<int> &vec, int start, int end) {
  return std::accumulate(vec.begin() + start, vec.begin() + end, 0);
}

int parallel_sum(std::vector<int> &vec) {
  int numThreads = 100;
  std::vector<int> results(numThreads);
  std::vector<std::future<int>> futures;

  for (int i = 0; i < numThreads; ++i) {
    int start = i * 10;
    int end = start + 10;
    futures.push_back(std::async(std::launch::async, partial_sum,
                                 std::cref(vec), start, end));
  }

  for (int i = 0; i < numThreads; ++i) {
    results[i] = futures[i].get();
  }

  while (numThreads > 1) {
    numThreads /= 2;
    futures.clear();
    for (int i = 0; i < numThreads; i++) {
      futures.push_back(std::async(
          std::launch::async, [](int a, int b) { return a + b; },
          results[2 * i], results[2 * i + 1]));
    }

    for (int i = 0; i < numThreads; i++) {
      results[i] = futures[i].get();
    }
  }

  return results[0];
}

int main(int argc, char *argv[]) {
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
