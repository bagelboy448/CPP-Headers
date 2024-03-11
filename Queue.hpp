//	=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//	Designer: Ashton Cox
//	Version: 1.0.1
//	Last Modified: March 10, 2024
//	=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//	A 'queue' is a linear data structure that stores elements sequentially. A queue follows the 'First In First Out' principle, where
//	elements are inserted at one end of the list and removed from the other. Thus, an element will not be processed until all the 
//	elements before it have been removed. As long as the default Push() and Pop() member functions are utilized, the queue retains 
//	the proper ordering of elements.

//	FUNCTION RETURN VALUES
//	======================
//	All non-accessor member functions are integer value returning functions. Their return values can be used to analyze the result of 
//  the function's execution. 
//	
//	RETURN VALUE   0	=>	 Successful execution.
//	RETURN VALUE  -1	=>	 Unsuccessful execution due to the queue being empty.
//	RETURN VALUE  -2	=>	 Unsuccessful execution due to an out-of-bounds position.
//	
//	THROW STATEMENTS
//	================
//	Accessor functions that simply return the data value stored somewhere in the queue utilize exceptions and throw statements. It is
//	the responsibility of the programmer to recognize when try... catch statements are necessary in a program to ensure safe execution.

//	DEPENDENCIES
//	============
//	iostream
//	stdexcept
//	============
	#pragma once

	#include <iostream>
	#include <stdexcept>
//	=====================
	
//	A queue is a data structure that efficiently manages a collection of elements by allowing insertion at one end and removal from the other, commonly used for tasks requiring first-in-first-out (FIFO) processing.
	template<typename T>
	class Queue {
	private:

//		Data elements are nodes which connect to one another, creating a singly linked list. Traversing such a list requires that each
//		element be accessed one after the other, from start to end.
//		===========================================================
		struct Node {

//			Contents:
//			=========
			T data;
			Node* next;
//			===========

//			Creation constructor
//			====================
			Node(T data) {
				this->data = data;
				next = nullptr; // links to nullptr by default
			} // Node()
//			===========

		}; // struct Node{}
//		===================

//		Private member variables
//		========================
		Node* first; // references to the first and last elements are always stored for fast accessing
		Node* last;
		int length;
//		===========

	public:

//		Default zero-parameter constructor
//		==================================
		Queue() {
			first = nullptr;
			last = nullptr;
			length = 0;
		} // Queue()
//		============

//		Utility Functions
//		========================================================
		bool IsEmpty() { return first == nullptr; } // IsEmpty()
		int Length() { return length; } // Length()
		Node* Peek() { return first; } // Peek()
//		========================================

//		Accessor Functions (THROW EXCEPTIONS)
//		=====================================
		T GetFirst() {
			if (IsEmpty()) {
				throw std::runtime_error("Attempted to access the first element of an empty queue.");
			}
			return first->data;
		} // GetFirst()

		T GetLast() {
			if (IsEmpty()) {
				throw std::runtime_error("Attempted to access the last element of an empty queue.");
			}
			return last->data;
		} // GetLast()

//		Returns the value at the specified position
		T Get(int position) {
			if (IsEmpty()) {
				throw std::runtime_error("Attempted to access an element in an empty queue.");
			} // if
			else if (position > length || position < 0) {
				throw std::runtime_error("Attempted to access an element in an invalid position.");
			} // else if
			Node* temp = first;
			for (int i = 0; i < position; i++) { // move to position to return
				temp = temp->next;
			} // for
			return temp->data;
		} // Get()
//		==========
		
//		Adds an element to the end of the queue
//		=======================================
		int Push(T data) {
			Node* newNode = new Node(data);
			if (IsEmpty()) {
				first = newNode;
				last = newNode;
			} // if
			else {
				last->next = newNode;
				last = newNode;
			} // else
			length++;
			return 0;
		} // Push()
//		===========

//		Adds an element to a specified position (0-indexed)
//		===================================================
		int Push(int position, T data) {
			if (IsEmpty() || position == length) {
				Insert(data);
				length++;
				return 0;
			} // if
			else if (position > length || position < 0) {
				return -2; // out of bounds
			} // else if
			else {
				Node* newNode = new Node(data);
				Node* temp = first;
				if (position == 0) {
					newNode->next = first;
					first = newNode;
					length++;
					return 0;
				} // if
				else {
					for (int i = 0; i < position - 2; i++) { // move to position before position to insert
						temp = temp->next;
					} // for
					newNode->next = temp->next;
					temp->next = newNode;
					length++;
					return 0;
				} // else
			} // else
		} // Push()
//		===========

//		Appends a target queue, leaving the target is unchanged
//		=======================================================
		int Merge(Node* target) {
			if (target == nullptr) {
				return -1; // empty target queue
			} // if
			else {
				while (target != nullptr) {
					last->next = target;
					last = target;
					target = target->next;
					length++;
				} // while
				return 0;
			} // else
		} // Merge()
//		============

//		Appends a target queue, erasing the target
//		==========================================
		int Merge(Queue<T> &target) {
			if (target.IsEmpty()) {
				return -1; // empty target queue
			} // if
			else {
				while (!target.IsEmpty()) {
					Push(target.GetFirst());
					target.Pop();
				} // while
				return 0;
			} // else
		} // Merge()
//		============

//		Removes the first element of the queue
//		======================================
		int Pop() {
			if (IsEmpty()) {
				return -1; // empty queue
			} // if
			else {
				Node* temp = first;
				first = first->next;
				delete temp;
				length--;
				return 0;
			} // else
		} // Pop()
//		==========

//		Removes an element at a specified position (0-indexed)
//		======================================================
		int Pop(int position) {
			if (IsEmpty()) {
				return -1; // queue empty
			} // if
			else if (position > length || position < 0) {
				return -2; // out of bounds
			} // else if
			else {
				Node* temp = first;
				for (int i = 0; i < position - 2; i++) { // move to position before position to insert
					temp = temp->next;
				} // for
				Node* target = temp->next;
				temp->next = temp->next->next;
				delete target;
				length--;
				return -1;
			} // else
		} // Pop()
//		==========

//		Removes the first n elements of the queue sequentially
//		======================================================
		int PopBatch(int number) {
			if (IsEmpty()) {
				return -1; // queue empty
			} // if
			else {
				for (int i = 0; i < number; i++) {
					Pop();
				} // for
				length -= number;
				return 0;
			} // else
		} // PopBatch()
//		===============

//		Removes every element in the queue and resets all variables
//		===========================================================
		int Clear() {
			if (IsEmpty()) {
				return -1; // empty queue
			} // if
			else {
				for (int i = 0; i < length; i++) {
					Pop();
				} // for
				Queue(); // Constructor call
				return 0;
			} // else
		} // Clear()
//		============

//		Prints the queue
//		================
		int Print() {
			if (IsEmpty()) {
				return -1; // empty queue
			} // if
			else {
				Node* temp = first;
				while (temp != nullptr) {
					std::cout << temp->data << std::endl;
					temp = temp->next;
				} // while
				return 0;
			} // else
		} // Print()
//		============

//		Prints the list in reverse order
//		================================
		int ReversePrint() {
			if (IsEmpty()) {
				return -1; // empty queue
			} // if
			else {
				ReversePrint(first);
			} // else
		} // ReversePrint()
//		===================

//		Recursive reverse print function
//		================================
		void ReversePrint(Node* ptr) {
			if (ptr->next != nullptr) {
				ReversePrint(ptr->next);
			} // if
			std::cout << ptr->data << std::endl;
		} // ReversePrint()
//		===================

	}; // class Queue{}
//	===================