#include "convert.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>
#include <vector>

// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}


std::vector< std::string > convert(const std::string & s1, const std::string & s2, const WordSet & words)
{
	std::vector<std::string> ret;

	// if either word not in dictionary, no path
	if (!words.contains(s1) || !words.contains(s2)) {
		return ret;
	}

    std::string letters = "abcdefghijklmnopqrstuvwxyz";
    std::map<std::string, std::string> graph; // map where keys are unique words, and value is word 1 letter off
    std::string oldWord, newWord = s2;
    
	std::queue <std::string> q; // q of words to find adj 1 letter off words too
    WordSet ws(11); // set of 'visited' words
    q.push(s2); // start at 
    while (!q.empty()) {
        newWord = oldWord = q.front();
		q.pop();
        for (unsigned i = 0; i < newWord.size(); ++i) {
            for (unsigned j = 0; j < letters.size(); ++j) {
				newWord[i] = letters[j]; // swap letter

				// check if the changed word is in dictionary and if we have seen it before
				if (words.contains(newWord) && !ws.contains(newWord)) {
						// queue up new word and set as visited
						q.push(newWord);
						ws.insert(newWord);
						graph[newWord] = oldWord; // map newly constructed word to old word 1 letter off
				}
            }

            newWord = oldWord; // reset word to unmodified
		}

		// we found shortest path to s1 by bfs
        if (ws.contains(s1)) 
            break;
    }

	// check that a path exists from s2 to s1 and vice versa
    if (ws.contains(s1)) {
		newWord = s1;
		ret.push_back(newWord);
		// start at s1 and get next word that is 1 letter off
        while (newWord != s2) {
            newWord = graph[newWord];
            ret.push_back(newWord);
        }
    }
	
    return ret;
}

