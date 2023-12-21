#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

const int kNumThreads = 4;
const int kNumIterations = 100000;

std::vector<int> shared_vector;
std::mutex mtx;

void worker_thread() {
    for (int i = 0; i < kNumIterations; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        shared_vector.push_back(i);
    }
}

int main() {
    std::vector<std::thread> threads;

    // TODO: Measure time for creating threads
    for (int i = 0; i < kNumThreads; ++i) {
        threads.emplace_back(worker_thread);
    }
    for (auto& thread : threads) {
        thread.join();
    }

    // Clear shared_vector for the next measurement
    shared_vector.clear();

    // TODO: Measure time for running without threads
    for (int i = 0; i < kNumThreads * kNumIterations; ++i) {
        shared_vector.push_back(i);
    }

    return 0;
}

