#ifndef __PROJ2_QUEUE_HPP
#define __PROJ2_QUEUE_HPP

#include "runtimeexcept.hpp"
#include <iostream>

class QueueEmptyException : public RuntimeException 
{
public:
	QueueEmptyException(const std::string & err) : RuntimeException(err) {}
};

template<typename Object>
struct Node {
	Node(Object value , Node * n = nullptr) : value(value), next(n) {}
	Node() {}
	Object value;
	Node * next;
};

template<typename Object>
class LLQueue
{
private:
	// fill in private member data here
	size_t tsize;
	Node<Object> *frontNode, *tailNode;


public:
	LLQueue(){
		frontNode = nullptr;
		tailNode = nullptr;
		this->tsize = 0;
	};

	// Note:  copy constructors are required.
	// Be sure to do a "deep copy" -- if I 
	// make a copy and modify one, it should not affect the other. 
	LLQueue(const LLQueue & st){
		frontNode = nullptr;
		tailNode = nullptr;
		this->tsize = 0;
		Node<Object> *tempNode = new Node<Object>;
		tempNode = st.frontNode;
		for (unsigned i = 0; i < st.tsize; i++) {
			enqueue(tempNode->value);
			tempNode = tempNode->next;
		}
	};
	LLQueue & operator=(const LLQueue & st) {
		if (this == &st) {
			return *this;
		}
		while (this->tsize > 0) {
			dequeue();
		}
		Node<Object> *tempNode = new Node<Object>;
		tempNode = st.frontNode;
		for (unsigned i = 0; i < st.tsize; i++) {
			enqueue(tempNode->value);
			tempNode = tempNode->next;
		}
		return *this;
	};
	~LLQueue()
	{
		// You need to implement the destructor also.
		while (this->tsize != 0){
			dequeue();
		}
	}

	size_t size() const noexcept {
		return this->tsize;
	};
	bool isEmpty() const noexcept {
		return size() == 0;
	};

	// We have two front() for the same reason the Stack in lecture week 2 had two top() functions.
	// If you do not know why there are two, your FIRST step needs to be to review your notes from that lecture.

	Object & front(){
		return frontNode->value;
	};

	const Object & front() const{
		const Object temp = frontNode->value;
		return temp;
	};

	void enqueue(const Object & elem){
		Node<Object> *tempNode = new Node<Object>;
		tempNode->value = elem;
		tempNode->next = nullptr;
		if (frontNode == nullptr) {
			frontNode = tempNode;
			tailNode = tempNode;
		}
		else {
			tailNode->next = tempNode;
			tailNode = tempNode;
		}
		tempNode = nullptr;
		this->tsize++;
	};

// does not return anything.  Just removes. 
	void dequeue() {
		if (isEmpty() == true) {
			throw QueueEmptyException("Queue is Empty Cannot Dequeue");
		}

		Node<Object> *tempNode = new Node<Object>;
		tempNode = frontNode;
		frontNode = frontNode->next;
		delete tempNode;
		this->tsize--;
		if (frontNode == nullptr) {
			tailNode = nullptr;
		}
	};
};

// TODO:  Fill in the functions here. 


#endif 
