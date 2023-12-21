#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <ctime>
#include <mutex>

// g++ PartB_comp_exc_bool_clock.cpp -o PartB_comp_exc_bool_clock -Wall -std=c++11 -fsanitize=thread -fPIE -pthread -pie
// ./PartB_comp_exc_bool_clock

const int kNumThreads = 4;
const int kNumIterations = 100000;

std::vector<int> shared_vector;
std::mutex mtx;
std::atomic<bool> lock{false};

std::vector<clock_t> thread_starttimes_clock;

void worker_thread() {
    mtx.lock();
    thread_starttimes_clock.push_back(clock());
    mtx.unlock();

    bool expected;
    for (int i = 0; i < kNumIterations; ++i) {
        expected = false;
        while (!lock.compare_exchange_weak(expected, true)) {
            expected = false;
        }
        shared_vector.push_back(i);
        lock = false;
    }

}

int main() {
    std::vector<std::thread> threads;

    // TODO: Measure time for creating threads
    
    std::clock_t before_time_1_clock;
    before_time_1_clock = std::clock();
    
    for (int i = 0; i < kNumThreads; ++i) {
        threads.emplace_back(worker_thread);
    }
    
    for (auto& thread : threads) {
        thread.join();
    }


    std::clock_t time_1_clock;
    time_1_clock = std::clock() - before_time_1_clock;
    std::cout << "Time(Clock) for thread creation loop and running was " << (float)time_1_clock/CLOCKS_PER_SEC << " seconds" << std::endl;

    for (long unsigned int i = 0; i < thread_starttimes_clock.size(); i++) {
        std::cout << "Thread with compare and exchange took " << (float)(thread_starttimes_clock[i]-before_time_1_clock)/CLOCKS_PER_SEC << " seconds to begin" << std::endl;
    }



    // Clear shared_vector for the next measurement
    shared_vector.clear();

    // TODO: Measure time for running without threads
   
    std::clock_t time_4_clock;
    time_4_clock = std::clock();

    
    for (int i = 0; i < kNumThreads * kNumIterations; ++i) {
        shared_vector.push_back(i);
    }


    time_4_clock = std::clock() - time_4_clock;
    std::cout << "Time(Clock) for running without threads was " << (float)time_4_clock/CLOCKS_PER_SEC << " seconds" << std::endl;


    return 0;
}

