#pragma once
#include <exception>
#include <string>
class NotDetectedFileName : public std::exception {
	int requiredSize;
public:
	NotDetectedFileName(int size) {
		requiredSize = size;
	}
	std::string message()const  {
		return "Ime fajla nije detektovano, unesite ime fajla sa ekstenzijom.Minimalna duizna imena sa ekstenzijom je " + std::to_string(requiredSize) + "\n";
	}
};

