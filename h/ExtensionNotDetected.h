#pragma once
#include <exception>
#include <string>
class ExtensionNotDetected :public std::exception{
	std::string extension;
public:
	ExtensionNotDetected(std::string extension) {
		this->extension = extension;
	};
	std::string message()const {
		return  "Nije detektovana ekstenzija  " + extension + " unesite ponovo!\n";
	}
};

