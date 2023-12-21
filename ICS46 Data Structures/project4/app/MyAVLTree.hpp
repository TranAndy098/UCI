#ifndef __PROJ_FOUR_AVL_HPP
#define __PROJ_FOUR_AVL_HPP

#include "runtimeexcept.hpp"
#include <string>
#include <vector>

class ElementNotFoundException : public RuntimeException 
{
public:
	ElementNotFoundException(const std::string & err) : RuntimeException(err) {}
};

// templated struct for node in binary tree
template<typename Key, typename Value>
struct node
{
	Key key;
    Value val;
    node<Key, Value> * left = nullptr;
    node<Key, Value> * right = nullptr;
	node<Key, Value> * parent = nullptr; // might not need
	size_t height = 0;
};

template<typename Key, typename Value>
class MyAVLTree
{
private:
	// fill in private member data here
	// If you need to declare private functions, do so here too.
	size_t _numNodes = 0;
	node<Key, Value> * _root = nullptr;

	node<Key, Value> * findNode(const Key &) const; // return specific node or nullptr
	void insert(node<Key, Value> *& currNode, node<Key, Value> * parent, const Key & k, const Value & v); // insert after givin node
	int getBalance(node<Key, Value> * currNode); // gets balance of a given node
	void updateHeight(node<Key, Value> * currNode); // update a nodes height
	void AVLTreeSetChild(node<Key, Value> * parent, std::string whichChild, node<Key, Value> * child); // code taken from zybooks 7.2
	void AVLTreeReplaceChild(node<Key, Value> * parent, node<Key, Value> * currentChild, node<Key, Value> * newChild); // code taken from zybooks 7.2
	void rebalance(node<Key, Value> * currNode, int balance); // rebalance a given node (subtree)
	void leftRotate(node<Key, Value> * currNode); // code taken from zybooks 7.2
	void rightRotate(node<Key, Value> * currNode); // code taken from zybooks 7.2

	// private functions to start at a specific node
	void inOrder(node<Key, Value> * root, std::vector<Key> & keys) const;
	void postOrder(node<Key, Value> * root, std::vector<Key> & keys) const;
	void preOrder(node<Key, Value> * root, std::vector<Key> & keys) const;

	void deleteTree(node<Key, Value> * root); // delete a tree

public:
	MyAVLTree();

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For this quarter, I am not requiring these. 
	//	MyAVLTree(const MyAVLTree & st);
	//	MyAVLTree & operator=(const MyAVLTree & st);


	// The destructor is, however, required. 
	~MyAVLTree();

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key & k) const; 

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const MyAVLTrees.
	Value & find(const Key & k);
	const Value & find(const Key & k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the AVL re-balance
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key & k, const Value & v);

	// in general, a "remove" function would be here
	// It's a little trickier with an AVL tree
	// and I am not requiring it for this quarter's ICS 46.
	// You should still read about the remove operation
	// in your textbook. 

	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;


};

// nothing needed to be done here because all handled in class declaration
template<typename Key, typename Value>
MyAVLTree<Key,Value>::MyAVLTree()
{

}

// private helper for recersive deletion of a tree
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::deleteTree(node<Key, Value> * root)
{
	if (root != nullptr) {
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}
}

template<typename Key, typename Value>
MyAVLTree<Key,Value>::~MyAVLTree()
{
	deleteTree(_root);
	_root = nullptr;
}

template<typename Key, typename Value>
size_t MyAVLTree<Key, Value>::size() const noexcept
{
	return _numNodes;
}

template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::isEmpty() const noexcept
{
	return (_numNodes == 0);
}

// private function to return the found node or nullptr
template<typename Key, typename Value>
node<Key, Value> * MyAVLTree<Key, Value>::findNode(const Key &k) const
{
	node<Key, Value> * temp = _root;

	// while temp isnt null, and we havent found the key
	while (temp != nullptr && temp->key != k) {
		if (k < temp->key)
			temp = temp->left;
		else
			temp = temp->right;
	}

	return temp;
}

template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::contains(const Key &k) const
{
	node<Key, Value> * temp = findNode(k);
	return (temp != nullptr);
}



template<typename Key, typename Value>
Value & MyAVLTree<Key, Value>::find(const Key & k)
{
	if (!contains(k))
		throw ElementNotFoundException("Element with key not found.");

	return findNode(k)->val;
}

template<typename Key, typename Value>
const Value & MyAVLTree<Key, Value>::find(const Key & k) const
{
	if (!contains(k))
		throw ElementNotFoundException("Element with key not found.");

	return findNode(k)->val;
}

// return balance of a single node
template<typename Key, typename Value>
int MyAVLTree<Key, Value>::getBalance(node<Key, Value> * currNode)
{
	int left = currNode->left == nullptr ? -1 : currNode->left->height;
	int right = currNode->right == nullptr ? -1 : currNode->right->height;

	return left - right;
}

// update a nodes height
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::updateHeight(node<Key, Value> * currNode)
{
	int leftHeight = currNode->left == nullptr ? -1 : currNode->left->height;
	int rightHeight = currNode->right == nullptr ? -1 : currNode->right->height;

	// make 1 more than max of the 2 heights
	if (leftHeight >= rightHeight)
		currNode->height = leftHeight + 1;
	else
		currNode->height = rightHeight + 1;
}

// code taken from zybooks 7.2
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::AVLTreeSetChild(node<Key, Value> * parent, std::string whichChild, node<Key, Value> * child) {
   if (whichChild == "left")
      parent->left = child;
   else
      parent->right = child;

   if (child != nullptr)
      child->parent = parent;

   updateHeight(parent);
}

// code taken from zybooks 7.2
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::AVLTreeReplaceChild(node<Key, Value> * parent, node<Key, Value> * currentChild, node<Key, Value> * newChild) {
   if (parent->left == currentChild)
      AVLTreeSetChild(parent, "left", newChild);
   else if (parent->right == currentChild)
      AVLTreeSetChild(parent, "right", newChild);
}

// left rotation ... code taken from zybooks 7.2
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::leftRotate(node<Key, Value> * currNode)
{
	node<Key, Value> * rightLeftChild = currNode->right->left;
	if (currNode->parent != nullptr)
		AVLTreeReplaceChild(currNode->parent, currNode, currNode->right);
	else { // node is root
		_root = currNode->right;
		_root->parent = nullptr;
	}
	AVLTreeSetChild(currNode->right, "left", currNode);
	AVLTreeSetChild(currNode, "right", rightLeftChild);
}

// right rotation ... code taken from zybooks 7.2
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::rightRotate(node<Key, Value> * currNode)
{
	node<Key, Value> * leftRightChild = currNode->left->right;
	if (currNode->parent != nullptr)
		AVLTreeReplaceChild(currNode->parent, currNode, currNode->left);
	else { // node is root
		_root = currNode->left;
		_root->parent = nullptr;
	}
	AVLTreeSetChild(currNode->left, "right", currNode);
	AVLTreeSetChild(currNode, "left", leftRightChild);
}

// rebalance a node as needed
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::rebalance(node<Key, Value> * currNode, int balance)
{
	// left heavy
	if (balance == 2) {
		// left rotate
		if (getBalance(currNode->left) == -1)
			leftRotate(currNode->left);

		// now right rotate
		rightRotate(currNode);
	}
	// right heavy
	else {
		// right rotate
		if (getBalance(currNode->right) == 1)
			rightRotate(currNode->right);

		// now left rotate
		leftRotate(currNode);
	}
}

// private helper function for recursive insert
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(node<Key, Value> *& currNode, node<Key, Value> * parent, const Key & k, const Value & v)
{
	// put on new leaf node
	if (currNode == nullptr) {
		currNode = new node<Key, Value>();
		currNode->key = k;
		currNode->val = v;
		currNode->parent = parent; // update parent
	}
	// internal node
	else {
		if (k < currNode->key)
			insert(currNode->left, currNode, k, v);
		else
			insert(currNode->right, currNode, k, v);

		// check if we need to rebalance
		int balance = getBalance(currNode);
		if (balance > 1 || balance < -1) {
			rebalance(currNode, balance);
		}

		updateHeight(currNode); // update height
	}
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(const Key & k, const Value & v)
{
	insert(_root, nullptr, k, v);
	++_numNodes;
}

// private function for recursive inOrder transversal
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::inOrder(node<Key, Value> * root, std::vector<Key> & keys) const
{
	if (root != nullptr) {
		inOrder(root->left, keys);
		keys.push_back(root->key);
		inOrder(root->right, keys);
	}
}

template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::inOrder() const
{
	std::vector<Key> foo;
	inOrder(_root, foo);
	return foo; 
}

// private function for recursive preOrder transversal
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::preOrder(node<Key, Value> * root, std::vector<Key> & keys) const
{
	if (root != nullptr) {
		keys.push_back(root->key);
		preOrder(root->left, keys);
		preOrder(root->right, keys);
	}
}

template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::preOrder() const
{
	std::vector<Key> foo;
	preOrder(_root, foo);
	return foo; 
}

// private function for recursive postOrder transversal
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::postOrder(node<Key, Value> * root, std::vector<Key> & keys) const
{
	if (root != nullptr) {
		postOrder(root->left, keys);
		postOrder(root->right, keys);
		keys.push_back(root->key);
	}
}

template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::postOrder() const
{
	std::vector<Key> foo;
	postOrder(_root, foo);
	return foo; 
}







#endif 