#include "MusicalSymbol.h"

MusicalSymbol::MusicalSymbol(Fraction duration){
	this->duration = duration;
}

void MusicalSymbol::setDuration(Fraction duration) {
	this->duration = duration;
}

void MusicalSymbol::setSymbolAsFirstPair() {
	setSymbolAsPair();
	firstPart = true;
}

void MusicalSymbol::setSymbolAsPair() {
	duration = Fraction::eight;
	partOfSymbol = true;
}
