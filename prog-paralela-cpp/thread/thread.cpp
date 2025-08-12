#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>

void hello() {
  std::this_thread::sleep_for(std::chrono::seconds{1});
  std::cout << "Hi my wigga" << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "Hello from main thread" << std::endl;
  std::thread sec{hello};
  std::thread secLambda{[]() {
    std::this_thread::sleep_for(std::chrono::seconds{2});
    std::cout << "Hi my wigga 2" << std::endl;
  }};

  sec.join();
  secLambda.join();
  return 0;
}
