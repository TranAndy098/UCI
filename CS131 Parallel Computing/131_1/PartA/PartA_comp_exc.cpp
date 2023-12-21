#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>

// g++ PartA_comp_exc.cpp -o PartA_comp_exc -Wall -std=c++11 -fsanitize=thread -fPIE -pthread -pie
// ./PartA_comp_exc

std::vector<int> vec;

std::atomic<int> ai;
std::atomic<bool> lock{false};

void increment() {
    bool expected;
    for (int i = 0; i < 1000000; ++i) {
        expected = false;
        while (!lock.compare_exchange_strong(expected, true)) {
            expected = false;
        }
        vec.push_back(i);
        lock = false;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Vector size: " << vec.size() << std::endl;
    return 0;
}


