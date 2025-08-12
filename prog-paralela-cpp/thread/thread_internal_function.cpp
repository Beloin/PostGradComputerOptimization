#include <chrono>
#include <functional>
#include <iostream>
#include <ostream>
#include <thread>

void hello(std::string &name, std::string surname) {
  std::this_thread::sleep_for(std::chrono::seconds{1});
  name = "Oi!";
  std::cout << "Hi " << name << " - " << surname << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "Hello from main thread" << std::endl;

  std::string john = "john";
  std::string smith = "Smith";
  // std::thread sec{hello, std::ref(john), smith};
  // sec.join();

  std::cout << "MAIN: " << john << " - " << smith << std::endl;
  return 0;
}
