#pragma once
#include <exception>
#include <iostream>
class BadInputFile :public std::exception {
	std::string exceptionMessage;
public:
	BadInputFile(std::string message) {
		this->exceptionMessage = message;
	}
	virtual std::string message() const {
		return exceptionMessage;
	}


};

