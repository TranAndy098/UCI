#ifndef __PROJ_2_HPP
#define __PROJ_2_HPP

#include <vector>
#include "LLQueue.hpp"

// Friends is a vector where friends[i] is the list of who person i is friends with.
//		Friendship  may be assumed to be symmetric for this project.
//		Note that this describes an undirected graph.
// The other two vectors are initially empty and are the same size as friends.
// Your assignment is to fill them with the relevant values;  when you return, for all i:
//		pathLengths[i] will be the length of the shortest path from start to i in the graph described by "friends"
//		numShortestPaths[i] will be the number of shortest paths from start to i in the graph so described.
//				Note that a path, in this context, may not repeat a vertex (person).
// You are encouraged to read proj2tests.cpp in the gtest folder and attempt the three graph cases by hand.
void countPaths(const std::vector< std::vector<unsigned> > & friends, unsigned start, std::vector<unsigned> & pathLengths, std::vector<unsigned> & numShortestPaths);



#endif 
