#include <future>
#include <iostream>
#include <thread>

using namespace std::literals;

void produce(std::promise<int> &px) {
  int x = 77;
  std::this_thread::sleep_for(2s);
  std::cout << "Promise define o seguinte valor compartilhado: " << x << '\n';
  px.set_value(x);
}

void consume(std::future<int> &fx) {
  std::cout << "Future executando get()...\n";
  int x = fx.get(); // Blocked till result
  std::cout << "Future obtem o valor do get(): " << x << '\n';
}

int main() {
  std::promise<int> prom;
  std::future<int> fut = prom.get_future();

  std::thread thr_producer{produce, std::ref(prom)};
  std::thread thr_consumer(consume, std::ref(fut));

  thr_consumer.join();
  thr_producer.join();
  return 0;
}
