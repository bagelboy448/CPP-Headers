#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "Queue.hpp"

using std::cout;
using std::endl;

template <typename T>
class QueueMenu {

private:

	enum operation { 
		length, getfirst, getlast, get, 
		push, pushpos, pop, poppos, 
		popbatch, clear, print, reverseprint,
		undef
	};

	Queue<T> queue;
	std::string inputString;
	std::vector<std::string> inputElements;
	operation userSelection;

public:

	QueueMenu() {
		inputString = "";
		inputElements.clear();
		userSelection = undef;
	}

	void QueryUser() {
		inputElements.clear();

		cout << "Input: ";
		std::getline(std::cin, inputString);

		std::stringstream ss(inputString);
		std::string element;
		while (ss >> element) {
			inputElements.push_back(element);
		}
	}

	void StringToEnum(const std::string &input) {
		if (input == "length") userSelection = length;
		else if (input == "getfirst") userSelection = getfirst;
		else if (input == "getlast") userSelection = getlast;
		else if (input == "get") userSelection = get;
		else if (input == "push") userSelection = push;
		else if (input == "pushpos") userSelection = pushpos;
		else if (input == "pop") userSelection = pop;
		else if (input == "poppos") userSelection = poppos;
		else if (input == "popbatch") userSelection = popbatch;
		else if (input == "clear") userSelection = clear;
		else if (input == "print") userSelection = print;
		else if (input == "reverseprint") userSelection = reverseprint;
		else userSelection = undef;
	}

	void ProcessCommand() {
		
		switch (userSelection) {
		case length:
			cout << "Queue length: " << queue.Length() << endl;
			break;

		case getfirst:
			try {
				cout << "First element: " << queue.GetFirst() << endl;
			} 
			catch(const std::runtime_error& ex) {
				std::cout << ex.what() << endl;
			}
			break;
		case getlast:
			try {
				cout << "Last element: " << queue.GetLast() << endl;
			}
			catch (const std::runtime_error& ex) {
				std::cout << ex.what() << endl;
			}
			break;
		case get:
			int position;
			try {
				position = std::stoi(inputElements[1]);
				try {
					cout << "First element: " << queue.Get(position) << endl;
				}
				catch (const std::runtime_error& ex) {
					std::cout << ex.what() << endl;
				}
			}
			catch (const std::invalid_argument& ia) {
				std::cerr << "Invalid argument: " << ia.what() << std::endl;
			}
			catch (const std::out_of_range& oor) {
				std::cerr << "Out of range: " << oor.what() << std::endl;
			}
			break;
		case push:
			int value;
			try {
				value = std::stoi(inputElements[1]);
				queue.Push(value);
				cout << value << " pushed into queue." << endl;
			}
			catch (const std::invalid_argument& ia) {
				std::cerr << "Invalid argument: " << ia.what() << std::endl;
			}
			catch (const std::out_of_range& oor) {
				std::cerr << "Out of range: " << oor.what() << std::endl;
			}
			break;
		case pushpos:
			int position, value;
			try {
				position = std::stoi(inputElements[1]);

				try {
					value = std::stoi(inputElements[2]);
					queue.Push(position, value);
				}
				catch (const std::invalid_argument& ia) {
					std::cerr << "Invalid argument: " << ia.what() << std::endl;
				}
				catch (const std::out_of_range& oor) {
					std::cerr << "Out of range: " << oor.what() << std::endl;
				}
			}
			catch (const std::invalid_argument& ia) {
				std::cerr << "Invalid argument: " << ia.what() << std::endl;
			}
			catch (const std::out_of_range& oor) {
				std::cerr << "Out of range: " << oor.what() << std::endl;
			}
		}
			

	}

};