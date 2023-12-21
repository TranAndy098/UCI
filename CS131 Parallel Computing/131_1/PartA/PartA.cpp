#include <iostream>
#include <vector>
#include <thread>

std::vector<int> vec;

void increment() {
    for (int i = 0; i < 1000000; ++i) {
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


