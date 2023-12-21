#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <mutex>

// g++ PartB_comp_exc_high_res.cpp -o PartB_comp_exc_high_res -Wall -std=c++11 -fsanitize=thread -fPIE -pthread -pie
// ./PartB_comp_exc_high_res

const int kNumThreads = 4;
const int kNumIterations = 100000;

std::vector<int> shared_vector;
std::mutex mtx;
std::atomic<int> size(0);

std::vector<std::chrono::high_resolution_clock::time_point> thread_starttimes_hrc;

void worker_thread() {
    mtx.lock();
    thread_starttimes_hrc.push_back(std::chrono::high_resolution_clock::now());
    mtx.unlock();

    for (int i = 0; i < kNumIterations; ++i) {
       int expected = size;
       while (!size.compare_exchange_weak(expected, expected + 1)) {
           expected = size;
       }
       shared_vector[expected] = i;

}
}

int main() {
    std::vector<std::thread> threads;
    shared_vector.resize(kNumThreads * kNumIterations);

    // TODO: Measure time for creating threads

    std::chrono::high_resolution_clock::time_point before_1_hrc = std::chrono::high_resolution_clock::now();
    

    for (int i = 0; i < kNumThreads; ++i) {
        threads.emplace_back(worker_thread);
    }
    
    for (auto& thread : threads) {
        thread.join();
    }

    std::chrono::high_resolution_clock::time_point after_1_hrc = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_1_hrc = std::chrono::duration_cast<std::chrono::duration<double>>(after_1_hrc-before_1_hrc);
    std::cout << "Time(HRC) for thread creation loop and running was " << time_1_hrc.count() << " seconds" << std::endl;

    for (long unsigned int i = 0; i < thread_starttimes_hrc.size(); i++) {
        std::cout << "Thread with compare and exchange took " << std::chrono::duration_cast<std::chrono::duration<double>>(thread_starttimes_hrc[i]-before_1_hrc).count() << " seconds to begin" << std::endl;
    }



    // Clear shared_vector for the next measurement
    shared_vector.clear();

    // TODO: Measure time for running without threads

    std::chrono::high_resolution_clock::time_point before_4_hrc = std::chrono::high_resolution_clock::now();
   
    
    for (int i = 0; i < kNumThreads * kNumIterations; ++i) {
        shared_vector.push_back(i);
    }

    std::chrono::high_resolution_clock::time_point after_4_hrc = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_4_hrc = std::chrono::duration_cast<std::chrono::duration<double>>(after_4_hrc-before_4_hrc);
    std::cout << "Time(HRC) for running without threads was " << time_4_hrc.count() << " seconds" << std::endl;


    return 0;
}

