#include "LinearSystem.h"

bool LinearSystem::addTakt(Takt* takt) {
	takts.push_back(takt);
	return true;
}
void LinearSystem::clear() {
	for (auto& takt : takts) {
		delete takt;
		takt = nullptr;
	}
}
LinearSystem::LinearSystem(Fraction duration) {
	this->duration = duration;
	current = new Takt(duration);
}
bool LinearSystem::addSymbol(MusicalSymbol* symbol) throw(BadInputFile) {
	if (!current->addSymbol(symbol)) {
		if (symbol->getDuration() == Fraction::eight) throw BadInputFile("Ne bi trebalo da se desi.\n");
		MusicalSymbol* symbol1 = symbol->makeCopy();
		symbol1->setSymbolAsFirstPair();
		symbol1->setDuration(Fraction::eight);
		MusicalSymbol* symbol2 = symbol->makeCopy();
		symbol2->setSymbolAsPair();
		symbol2->setDuration(Fraction::eight);
		symbol1->connectSymbols(symbol2);
		if (!current->addSymbol(symbol1)) throw BadInputFile("Ne bi trebalo da se desi.\n");
		current->setTaktID(taktID++);
		addTakt(current);
		current = new Takt(duration);
		current->addSymbol(symbol2);
	}

	if (current->isFull()) {
		current->setTaktID(taktID++);
		addTakt(current);
		current = new Takt(duration);
	}
	return true;

}
void LinearSystem::disconect() {
	for (auto& takt : takts) {
		takt = nullptr;
	}
	current = nullptr;
}
LinearSystem::~LinearSystem() {
	this->clear();
	delete current;
	current = nullptr;

}

