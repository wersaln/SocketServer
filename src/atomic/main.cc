#include <future>
#include <iostream>
#include <atomic>

volatile std::atomic_size_t value;

int loop(bool inc, int limit) {
  std::cout << "Started " << inc << " " << limit << std::endl;
  for (int i = 0; i < limit; ++i) {
    if (inc) {
      ++value;
    } else {
      --value;
    }
  }
  return 0;
}

int main() {
  value = 0;
  auto f = std::async(std::launch::async, std::bind(loop, true, 200000000));
  loop(false, 100000000);
  f.wait();
  std::cout << value << std::endl;
}
