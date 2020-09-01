#pragma once
#include <exception>
#include <string>
class ForbiddenCharacters :public std::exception{
public:
	std::string message()const {
		return "Oznake '[', ']', '|' i ' ' se koriste kao nesto drugo, ne mogu da oznacavaju notu!\n";
	}

};

