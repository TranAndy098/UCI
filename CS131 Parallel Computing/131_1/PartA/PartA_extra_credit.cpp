#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// g++ PartA_extra_credit.cpp -o PartA_extra_credit -Wall -std=c++11 -fsanitize=thread -fPIE -pthread -pie
// ./PartA_extra_credit

std::vector<int> vec;

void increment() {
    for (int i = 0; i < 1000000; ++i) {
        vec.push_back(i);
    }
}

int main() {
    std::thread t1(increment);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Vector size: " << vec.size() << std::endl;
    return 0;
}


