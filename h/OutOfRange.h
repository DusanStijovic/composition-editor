#pragma once
#include <exception>
#include <iostream>
#include<string>
class OutOfRange :public std::exception{
	int low, high;
public:

	OutOfRange(int low, int high) {
		this->low = low;
		this->high = high;
	}
	std::string  message() const {
		return "Uneli ste broj van opsega, unesite broj izmedju " + std::to_string(low) + " i " + std::to_string(high) + "\n";
	}
};

