#include "gtest/gtest.h"
#include "MyAVLTree.hpp"
#include "proj4.hpp"
#include <string>
#include <sstream>
#include <vector>

namespace{


// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.

// The four tests marked "CheckPoint" are going to be run
// on your submission for the checkpoint code.
// This is worth one-sixth of your grade on the assignment
// and is due at the time marked "checkpoint"


// None of the "checkpoint" tests require you to have
// AVL functionality OR the counting of words.
// Implementing your tree as a plain binary search
// tree is more than enough to pass these tests.

// Of course, you are expected to implement AVL functionality
// for the full project.

// BE SURE TO FULLY TEST YOUR CODE.
// This means making sure your templating is not hard-coding for 
// a specific type, that every function is called somewhere in 
// your test cases, etc. 
// There will NOT be a project 2 style redo for this;  if your 
//  code does not compile, your score will be a zero. 


TEST(CheckPoint, CheckPoint_FindTheRoot)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");

	EXPECT_TRUE( tree.contains(5) );
}

TEST(CheckPoint, CheckPoint_FindOneHop)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(10, "bar");

	EXPECT_TRUE( tree.contains(10) );
}

TEST(CheckPoint, CheckPoint_FindTwoHops)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");

	EXPECT_TRUE( tree.contains(12) );
}



TEST(CheckPoint, CheckPoint_Add5)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");
	tree.insert(15, "fifteen");

	EXPECT_TRUE( tree.size() == 5 );
}



TEST(PostCheckPoint, InOrderTraversal)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");
	tree.insert(15, "fifteen");

	std::vector<int> trav = tree.inOrder();
	std::vector<int> expected = {3, 5, 10, 12, 15};
	EXPECT_TRUE( trav == expected );
}

TEST(OurTests, Rebalance1)
{
	MyAVLTree<int, int> tree;
	for (int i=0; i<3; ++i)
		tree.insert(i,i);

	std::vector<int> trav = tree.preOrder();
	std::vector<int> expected = {1,0,2};

	EXPECT_TRUE( trav == expected );
}

TEST(OurTests, Rebalance2)
{
	MyAVLTree<int, int> tree;
	for (int i=0; i<5; ++i)
		tree.insert(i,i);

	std::vector<int> trav = tree.preOrder();
	std::vector<int> expected = {1,0,3,2,4};

	EXPECT_TRUE( trav == expected );
}

TEST(OurTests, Rebalance3)
{
	MyAVLTree<int, int> tree;
	for (int i=0; i<10; ++i)
		tree.insert(i,i);

	std::vector<int> trav = tree.preOrder();
	std::vector<int> expected = {3,1,0,2,7,5,4,6,8,9};

	EXPECT_TRUE( trav == expected );
}

// 1,2,3,12,9,4,7,5,13,15,6,16,14,17
TEST(OurTests, Rebalance4)
{
	MyAVLTree<int, int> tree;
	std::vector<int> toAdd = {1,2,3,12,9,4,7,5,13,15,6,16,14,17};
	for (int i=0; i<toAdd.size(); ++i)
		tree.insert(toAdd[i],toAdd[i]);

	std::vector<int> pre = tree.preOrder();
	std::vector<int> in = tree.inOrder();
	std::vector<int> post = tree.postOrder();

	std::vector<int> expectedPre = {5,3,2,1,4,9,7,6,15,13,12,14,16,17};
	std::vector<int> expectedIn = {1,2,3,4,5,6,7,9,12,13,14,15,16,17};
	std::vector<int> expectedPost = {1,2,4,3,6,7,12,14,13,17,16,15,9,5};

	EXPECT_TRUE( pre == expectedPre );
	EXPECT_TRUE( in == expectedIn );
	EXPECT_TRUE( post == expectedPost );
}

TEST(OurTests, Rebalance5)
{
	MyAVLTree<std::string, int> tree;
	std::vector<int> toAdd = {1,2,3,12,9,4,7,5,13,15,6,16,14,17};
	for (int i=0; i<toAdd.size(); ++i) {
		char c = 'a'+toAdd[i]-1;
		tree.insert(std::string("")+c,toAdd[i]);
	}

	std::vector<std::string> pre = tree.preOrder();
	std::vector<std::string> in = tree.inOrder();
	std::vector<std::string> post = tree.postOrder();

	std::vector<std::string> expectedPre = {"e","c","b","a","d","i","g","f","o","m","l","n","p","q"};
	std::vector<std::string> expectedIn = {"a","b","c","d","e","f","g","i","l","m","n","o","p","q"};
	std::vector<std::string> expectedPost = {"a","b","d","c","f","g","l","n","m","q","p","o","i","e"};

	EXPECT_TRUE( pre == expectedPre );
	EXPECT_TRUE( in == expectedIn );
	EXPECT_TRUE( post == expectedPost );
	EXPECT_FALSE( tree.isEmpty() );
	EXPECT_TRUE( tree.size() == 14 );
	EXPECT_TRUE ( tree.contains("l") );
	EXPECT_FALSE ( tree.contains("z") );
}

TEST(OurTests, TestFind)
{
	MyAVLTree<std::string, int> tree;
	tree.insert("foo", 3);
	tree.insert("sna", 5);
	tree.insert("bar", 10);
	tree.insert("twelve", 12);
	tree.insert("fifteen", 15);

	EXPECT_TRUE( tree.find("twelve") == 12 );
}

TEST(OurTests, TestFind2)
{
	MyAVLTree<std::string, std::string> tree;
	tree.insert("foo", "three");
	tree.insert("sna", "five");
	tree.insert("bar", "ten");
	tree.insert("twelve", "twelve");
	tree.insert("fifteen", "fifteen");

	EXPECT_TRUE( tree.find("twelve") == "twelve");
}


TEST(PostCheckPoint, JackSparrow)
{
	std::string quote = "I'm dishonest, and a dishonest man you can ";
	quote += "always trust to be dishonest. Honestly. It's the honest ";
	quote += "ones you want to watch out for, because you can never ";
	quote += "predict when they're going to do something incredibly... stupid.";

	std::istringstream stream( quote );

	MyAVLTree<std::string, unsigned> tree;

	countWords(stream, tree);
	
	EXPECT_TRUE(tree.find("dishonest") == 3);
}

}