#include <chrono>
#include <functional>
#include <iostream>
#include <ostream>
#include <thread>

class Hello {
public:
  void hi(std::string &name) {
    name = "Jair Messias";
    std::cout << "Hello: " << name << std::endl;
  }
};

int main(int argc, char *argv[]) {
  std::cout << "Hello from main thread" << std::endl;

  Hello myhello{};
  std::string john = "john";
  std::string smith = "Smith";
  std::thread sec{&Hello::hi, &myhello, std::ref(john)};
  sec.join();

  std::cout << "MAIN: " << john << " - " << smith << std::endl;
  return 0;
}
