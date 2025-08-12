

#include <future>
#include <iostream>
#include <ostream>
#include <thread>

using namespace std::literals;

int hello() {
  std::cout << "hello" << std::endl;
  return 1;
}

int main(int argc, char *argv[]) {
  auto future = std::async(std::launch::async, hello);
  // std::launch::async
  // std::launch::deferred;

  std::this_thread::sleep_for(1s);
  auto res = future.get();
  std::cout << "Recv: " << res << std::endl;
  return 0;
}
