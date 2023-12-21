#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

// g++ PartA_mutex.cpp -o PartA_mutex -Wall -std=c++11 -fsanitize=thread -fPIE -pthread -pie
// ./PartA_mutex

std::vector<int> vec;
std::mutex mtx;

void increment() {
    for (int i = 0; i < 1000000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        
        vec.push_back(i);
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


