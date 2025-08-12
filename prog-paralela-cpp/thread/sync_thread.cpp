#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>

using namespace std::literals;

std::mutex mutex;
std::condition_variable condVar;
// Predicate var
bool isReady = false;

int wait_var(){
  std::this_thread::sleep_for(1s);
  std::unique_lock<std::mutex> lock{mutex};
  std::cout << "Waiting for var" << std::endl;
  condVar.wait(lock, [] {
    return isReady;
  });
  std::cout << "Released from var" << std::endl;

  return 0;
}

int grant() {
  {
    std::unique_lock<std::mutex> lock{mutex};
    std::cout<< "Liberando o toin antes da hora" << std::endl;
  }

  condVar.notify_all();
  isReady = true;
    
  return 0;
}

int main(int argc, char *argv[]) {
  std::thread t1{wait_var};
  std::thread t2{grant};

  t1.join(); t2.join();
  
  return 0;
}
