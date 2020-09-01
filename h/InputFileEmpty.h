#pragma once
#include <exception>
#include <string>
class InputFileEmpty :public std::exception{
public:
	std::string message()const {
		return "Ulazni fajl je prazan!\n";
	}
};

