#include "gtest/gtest.h"
#include "proj0.hpp"
#include <unordered_map>
#include <string>

// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.


namespace{

TEST(VerifySolution, First){
    std::string s1 = "POT";
    std::string s2 = "PAN";
    std::string s3 = "BIB";

    std::unordered_map<char, unsigned> solution = { {'A', 7}, {'B', 5}, 
        {'I', 0}, {'N', 4}, {'O', 3}, {'P', 2}, {'T', 1}
    };

    EXPECT_TRUE( verifySolution( s1, s2, s3, solution ) );
}

TEST(VerifySolution, Second){

    std::string s1 = "CAT";
    std::string s2 = "DOG";
    std::string s3 = "PIG";

    std::unordered_map<char, unsigned> solution = { {'A', 5}, {'C', 2}, {'D', 1}, {'G', 6}, {'I', 9}, {'O', 4}, {'P', 3}, {'T', 0} };

    EXPECT_TRUE( verifySolution( s1, s2, s3, solution ) );
} // end test two


} // end namespace
