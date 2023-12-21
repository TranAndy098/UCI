#include "proj2.hpp"

#include <vector>
#include <iostream>
#include <string>


void countPaths(const std::vector< std::vector<unsigned> > & friends, unsigned start, std::vector<unsigned> & pathLengths, std::vector<unsigned> & numShortestPaths)
{
    /*
    //pathLengths
    for (unsigned i = 0; i < pathLengths.size(); i++) {
        std::vector<unsigned> visited(friends.size());
        std::vector<unsigned> needtovist(friends.size());
        std::vector<unsigned> goingtovist(friends.size());
        LLQueue<unsigned> lq;
        for (unsigned j = 0; j < visited.size(); j++) {
            visited[j] = 0;
            needtovist[j] = 0;
            goingtovist[j] = 0;
        }
        unsigned p = 0;
        unsigned long r = 0;
        lq.enqueue(start);
        needtovist[start] = 1;
        //std::cout << "start at: " << lq.front() << std::endl;
        //std::cout << "find at: " << i << std::endl;
        while (lq.front() != i) {
            //std::cout << "front: " << lq.front() << " r is " << r << std::endl;
            visited[lq.front()] = 1;
            if (r == 0) {
                for (unsigned k = 0; k < needtovist.size(); k++) {
                    //std::cout << "need to visit: " << k << "with " << needtovist[k] << std::endl;
                    if (needtovist[k] == 1) {
                        for (unsigned j = 0; j < friends[k].size(); j++) {
                            //std::cout << "inspecting: " << friends[k][j] << std::endl;
                            if (visited[friends[k][j]] == 0) {
                                //std::cout << "adding: " << friends[k][j] << std::endl;
                                if (goingtovist[friends[k][j]] == 0) {
                                    lq.enqueue(friends[k][j]);
                                    goingtovist[friends[k][j]] = 1;
                                }
                            }
                        }
                        needtovist[k] = 0;
                    }
                }
                r = friends[lq.front()].size();
                p += 1;
                for (unsigned j = 0; j < goingtovist.size(); j++) {
                    needtovist[j] = goingtovist[j];
                }
            }
            lq.dequeue();
            r--;
        }
        pathLengths[i] = p;
        //std::cout << "path for " << i << ": " << p << "\n" << std::endl;
        for (unsigned j = 0; j < lq.size(); j++) {
            lq.dequeue();
        }
    }
    */
     
    //numShortestPaths
    /*
    unsigned maxpaths = 0;
    for (unsigned j = 0; j < numShortestPaths.size(); j++) {
        maxpaths += 1;
    }
    for (unsigned j = 0; j < numShortestPaths.size(); j++) {
        numShortestPaths[j] = maxpaths;
    }
    */
    /*
    for (unsigned i = 0; i < numShortestPaths.size(); i++) {
        std::vector<unsigned> visited(friends.size());
        std::vector<unsigned> needtovist(friends.size());
        std::vector<unsigned> goingtovist(friends.size());
        LLQueue<unsigned> lq;
        for (unsigned j = 0; j < visited.size(); j++) {
            visited[j] = 0;
            needtovist[j] = 0;
            goingtovist[j] = 0;
        }
        unsigned p = 0;
        unsigned long r = 0;
        lq.enqueue(start);
        needtovist[start] = 1;
        //std::cout << "start at: " << lq.front() << std::endl;
        //std::cout << "find at: " << i << std::endl;
        while (lq.front() != i) {
            //std::cout << "front: " << lq.front() << " r is " << r << std::endl;
            visited[lq.front()] = 1;
            goingtovist[lq.front()] = 0;
            if (r == 0) {
                for (unsigned k = 0; k < needtovist.size(); k++) {
                    //std::cout << "need to visit: " << k << " with " << needtovist[k] << std::endl;
                    if (needtovist[k] >= 1) {
                        for (unsigned j = 0; j < friends[k].size(); j++) {
                            //std::cout << "inspecting: " << friends[k][j] << std::endl;
                            if (visited[friends[k][j]] == 0) {
                                //std::cout << "adding: " << friends[k][j] << std::endl;
                                if (goingtovist[friends[k][j]] == 0) {
                                    lq.enqueue(friends[k][j]);
                                }
                                goingtovist[friends[k][j]] += needtovist[k];
                            }
                        }
                        needtovist[k] = 0;
                    }
                }
                r = friends[lq.front()].size();
                p += 1;
                for (unsigned j = 0; j < goingtovist.size(); j++) {
                    needtovist[j] = goingtovist[j];
                }
            }
            lq.dequeue();
            r--;
        }
        pathLengths[i] = p;
        if (goingtovist[i] == 0) {
            goingtovist[i] = 1;
        }
        numShortestPaths[i] = goingtovist[i];
        //std::cout << "path for " << i << ": " << p << " with: " << numShortestPaths[i] << "\n" << std::endl;
        for (unsigned j = 0; j < lq.size(); j++) {
            lq.dequeue();
        }
    }
     */
    
    /*
        std::vector<unsigned> visited(friends.size());
        std::vector<unsigned> needtovist(friends.size());
        std::vector<unsigned> goingtovist(friends.size());
        LLQueue<unsigned> lq;
        for (unsigned j = 0; j < visited.size(); j++) {
            visited[j] = 0;
            needtovist[j] = 0;
            goingtovist[j] = 0;
        }
    unsigned i = friends.size();
    bool change = true;
    for (unsigned j = 0; j < pathLengths.size(); j++) {
        pathLengths[j] = i;
    }
        unsigned p = 0;
        unsigned long r = 0;
        lq.enqueue(start);
        needtovist[start] = 1;
        std::cout << "start at: " << lq.front() << std::endl;
        std::cout << "find at: " << i << std::endl;
        while (i > 0) {
            std::cout << "front: " << lq.front() << " r is " << r << std::endl;
            visited[lq.front()] = 1;
            //goingtovist[lq.front()] = 0;
            if (r == 0) {
                for (unsigned k = 0; k < needtovist.size(); k++) {
                    std::cout << "need to visit: " << k << " with " << needtovist[k] << std::endl;
                    if (needtovist[k] >= 1) {
                        for (unsigned j = 0; j < friends[k].size(); j++) {
                            std::cout << "inspecting: " << friends[k][j] << std::endl;
                            if (visited[friends[k][j]] == 0) {
                                std::cout << "adding: " << friends[k][j] << " with " << needtovist[k] << std::endl;
                                if (goingtovist[friends[k][j]] == 0) {
                                    lq.enqueue(friends[k][j]);
                                    r += 1;
                                }
                                goingtovist[friends[k][j]] += needtovist[k];
                                std::cout << "added: " << friends[k][j] << " with " << goingtovist[friends[k][j]] << std::endl;
                            }
                        }
                        needtovist[k] = 0;
                    }
                }
                //r = friends[lq.front()].size();
                
                std::cout << "1path is: " << p << " for " << lq.front() << std::endl;
                change = true;
                //p += 1;
                std::cout << "2path is: " << p << " for " << lq.front() << std::endl;
                for (unsigned j = 0; j < goingtovist.size(); j++) {
                    needtovist[j] = goingtovist[j];
                }
            }
            std::cout << "3path is: " << p << " for " << lq.front() << " with num: " << goingtovist[lq.front()] << std::endl;
            if (p < pathLengths[lq.front()]) {
            pathLengths[lq.front()] = p;
            if (goingtovist[lq.front()] == 0) {
                goingtovist[lq.front()] = 1;
            }
                    numShortestPaths[lq.front()] = goingtovist[lq.front()];
                std::cout << "path for " << lq.front() << ": " << p << " with: " << numShortestPaths[lq.front()] << "\n" << std::endl;
                i -= 1;
            }
            goingtovist[lq.front()] = 0;
            //needtovist[lq.front()] = 0;
            lq.dequeue();
            r--;
            if (change == true) {
                p += 1;
                change = false;
            }
            
        }
    */
    
    std::vector<unsigned> visited(friends.size());
    //std::vector<unsigned> needtovist(friends.size());
    //std::vector<unsigned> goingtovist(friends.size());
    LLQueue<unsigned> lq;
    LLQueue<unsigned> nvq;

    unsigned t = 1;
    //bool change = true;
    unsigned p = 0;
    //unsigned r = 0;
    lq.enqueue(start);
    //std::cout << "start at: " << lq.front() << std::endl;
    while (t > 0) {
        //std::cout << "front is: " << lq.front() << std::endl;
        if (lq.isEmpty()) {
            //std::cout << "here: " << nvq.size() << std::endl;
            p += 1;
            while (nvq.isEmpty() == false) {
                for (unsigned i = 0; i < friends[nvq.front()].size(); i++) {
                    std::cout << "inspecting: " << friends[nvq.front()][i] << std::endl;
                    if (visited[friends[nvq.front()][i]] == 0) {
                        std::cout << "adding: " << friends[nvq.front()][i] << std::endl;
                        lq.enqueue(friends[nvq.front()][i]);
                        //r += 1;
                    }

    
                }
                nvq.dequeue();
            }
            //std::cout << "end: " << nvq.size() << std::endl;
            if (lq.isEmpty()) {
                t = 0;
            }
        }
        
        else {
            std::cout << "front is: " << lq.front() << std::endl;
            pathLengths[lq.front()] = p;
            numShortestPaths[lq.front()] += 1;
            visited[lq.front()] += 1;
            nvq.enqueue(lq.front());
            lq.dequeue();
        }
        
    }
    
}
