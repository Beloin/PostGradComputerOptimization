#include <chrono>
#include <iostream>
#include <mutex>
#include <ratio>
#include <thread>

static std::mutex mutex;
static int result;

void tr() {
  std::unique_lock<std::mutex> lo{mutex};
  while (!mutex.try_lock()) {
    std::cout << "locked\n";
    std::this_thread::sleep_for(std::chrono::duration<std::milli>{1});
  }

  std::cout << "Sleeping\n";
  std::this_thread::sleep_for(std::chrono::seconds{6});
  std::cout << "Woke up\n";
}

int main(int argc, char *argv[]) {
  std::cout << "Mutex!" << std::endl;

  std::thread t1{tr};
  std::thread t2{tr};
  
  std::cout << "End\n";
  return 0;
}
