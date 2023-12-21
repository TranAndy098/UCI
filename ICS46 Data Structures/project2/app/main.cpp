#include "LLQueue.hpp"
#include "proj2.hpp"
#include <iostream>
#include <string>

int main()
{
    
    std::cout << "Test 1 -----------------------" << std::endl;
    
    std::vector< std::vector<unsigned> > g1 = {
        {1,2}, {0,3}, {0,3}, {1,2}
    };
        std::vector<unsigned> pathLengths(4);
    std::vector<unsigned> numShortestPaths(4);
    
    countPaths(g1, 0, pathLengths, numShortestPaths);

    std::vector<unsigned> expPathLengths = {0, 1, 1, 2};
    std::vector<unsigned> expNumSP = {1, 1, 1, 2};
    
    bool b11 = (pathLengths == expPathLengths);
    if (b11 == true) {
        std::cout << "pathLengths11 is true" << std::endl;
    }else {
        std::cout << "pathLengths11 is false" << std::endl;
    }
    bool b12 = (numShortestPaths == expNumSP);
    if (b12 == true) {
        std::cout << "pathLengths12 is true" << std::endl;
    }else {
        std::cout << "pathLengths12 is false" << std::endl;
    }
    
    for (unsigned j = 0; j < pathLengths.size(); j++) {
        std::cout << "shortest path to: " << j << " is " << pathLengths[j] << " with num of short paths: " << numShortestPaths[j] << std::endl;
    }
    
    
    std::cout << "Test 2 -----------------------" << std::endl;
    
    std::vector< std::vector<unsigned> > g12 = {
        {1, 2, 4}, {0,3}, {0,3}, {1,2,5}, {0, 5}, {3, 4}
    };
    
    std::vector<unsigned> pathLengths2(6);
    std::vector<unsigned> numShortestPaths2(6);
    
    countPaths(g12, 0, pathLengths2, numShortestPaths2);

    std::vector<unsigned> expPathLengths2 = {0, 1, 1, 2, 1, 2};
    std::vector<unsigned> expNumSP2 = {1, 1, 1, 2, 1, 1};
    
     bool b21 = (pathLengths2 == expPathLengths2);
     if (b21 == true) {
         std::cout << "pathLengths21 is true" << std::endl;
     }else {
         std::cout << "pathLengths21 is false" << std::endl;
     }
    bool b22 = (numShortestPaths2 == expNumSP2);
    if (b22 == true) {
        std::cout << "pathLengths22 is true" << std::endl;
    }else {
        std::cout << "pathLengths22 is false" << std::endl;
    }
    
    std::cout << "Test 3 -----------------------" << std::endl;
    
    std::vector< std::vector<unsigned> > g13 = {
        {1, 2, 4}, {0,3}, {0,3}, {1,2,5, 7}, {0, 5, 6}, {3, 4}, {4, 7}, {3, 6},
    };
    
    std::vector<unsigned> pathLengths3(8);
    std::vector<unsigned> numShortestPaths3(8);
    
    countPaths(g13, 0, pathLengths3, numShortestPaths3);

    std::vector<unsigned> expPathLengths3 = {0, 1, 1, 2, 1, 2, 2, 3};
          std::vector<unsigned> expNumSP3 = {1, 1, 1, 2, 1, 1, 1, 3};
    
     bool b31 = (pathLengths3 == expPathLengths3);
     if (b31 == true) {
         std::cout << "pathLengths31 is true" << std::endl;
     }else {
         std::cout << "pathLengths31 is false" << std::endl;
     }
    bool b32 = (numShortestPaths3 == expNumSP3);
    if (b32 == true) {
        std::cout << "pathLengths32 is true" << std::endl;
    }else {
        std::cout << "pathLengths32 is false" << std::endl;
    }
    
    
    std::cout << "hello" << std::endl;
    std::cout << "INTS LLQUEUES" << std::endl;
    LLQueue<int> lq1;
    
    lq1.enqueue(9);
    lq1.enqueue(8);
    lq1.enqueue(7);

    LLQueue<int> lq2 = lq1;

    std::cout << "LQ2 size: " << lq2.size() << std::endl;
    while (lq2.isEmpty() != true) {
        std::cout<< "LQ2 front: " << lq2.front() << std::endl;
        lq2.dequeue();
    }
    
    lq1.enqueue(6);
    lq1.enqueue(5);
    lq1.enqueue(4);

    std::cout << "LQ2 size: " << lq2.size() << std::endl;

    lq2 = lq1;

    std::cout << "LQ1 size: " << lq1.size() << std::endl;
    while (lq1.isEmpty() != true) {
        std::cout<< "LQ1 front: " << lq1.front() << std::endl;
        lq1.dequeue();
    }

    lq1.enqueue(3);
    lq1.enqueue(2);
    lq1.enqueue(1);

    std::cout << "LQ1 size: " << lq1.size() << std::endl;
    while (lq1.isEmpty() != true) {
        std::cout<< "LQ1 front: " << lq1.front() << std::endl;
        lq1.dequeue();
    }


    std::cout << "LQ2 size: " << lq2.size() << std::endl;
    while (lq2.isEmpty() != true) {
        std::cout<< "LQ2 front: " << lq2.front() << std::endl;
        lq2.dequeue();
    }

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "CHAR LLQUEUES" << std::endl;

    LLQueue<char> lqc;
    
    lqc.enqueue('A');
    lqc.enqueue('B');
    lqc.enqueue('C');
    lqc.enqueue('D');
    lqc.enqueue('E');
    lqc.enqueue('F');

    std::cout << "lqc size: " << lqc.size() << std::endl;
    while (lqc.isEmpty() != true) {
        std::cout<< "lqc front: " << lqc.front() << std::endl;
        lqc.dequeue();
    }

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "STRING LLQUEUES" << std::endl;

    LLQueue<std::string> lqs;
    
    lqs.enqueue("first");
    lqs.enqueue("second");
    lqs.enqueue("third");
    
    LLQueue<std::string> lqs2;
    lqs2 = lqs;
    
    lqs.enqueue("fourth");
    lqs.enqueue("fifth");
    lqs.enqueue("sixth");

    std::cout << "lqs size: " << lqs.size() << std::endl;
    while (lqs.isEmpty() != true) {
        std::cout<< "lqs front: " << lqs.front() << std::endl;
        lqs.dequeue();
    }
    
    std::cout << "lqs2 size: " << lqs2.size() << std::endl;
    while (lqs2.isEmpty() != true) {
        std::cout<< "lqs2 front: " << lqs2.front() << std::endl;
        lqs2.dequeue();
    }

    std::cout << "bye" << std::endl;
    
    return 0;
}

