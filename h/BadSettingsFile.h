#pragma once
#include <string>
#include "BadInputFile.h"
class BadSettingsFile :public BadInputFile{
public:
	BadSettingsFile() :BadInputFile("Format ulaznog fajla nije dobar!\n") {};
	std::string message() const {
		std::string description = BadInputFile::message();
		description += "Format fajla za podesavanje klavira je sledeci:\n";
		description += "Prvo ide taster na tastaturi koji oznacava neku notu, pa zapeta\n";
		description += "Posle zapete, bez razmaka ide nota koju oznacava ta dirka (A, B, C, D,E, F, G, H) pa # ako ima povisilicu inace nista\n";
		description += "Posle toga zapeta, bez razmaka midi broj i prelazak u novi red\n";
		description += "Ispravite dati fajl ili unesite neki koji je odgovarajuceg formata.\n";
		return description;
	}

};

