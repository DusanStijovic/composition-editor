#pragma once
#include <exception>
#include <string>
class BadCompositionFile :public std::exception{
public:
	std::string message()const {
		std::string description =  "Karakter u fajlu se ne nalazi u podesavanjima klavira.\n";
		description += "Unesite drugi fajl za kompoziciju ili promenite podesavanja klavira.\n";
		return description;
	}
};

