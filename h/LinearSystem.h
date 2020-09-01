#pragma once
#include <list>
#include "Takt.h"
#include "BadInputFile.h"
class LinearSystem {
	std::list<Takt*> takts;
	Takt* current;
	Fraction duration;
	int taktID = 1;
public:
	enum Pause { NO, YES };
	bool addTakt(Takt* takt);
	std::list<Takt*>& getTakts() {
		return takts;

	}
	const std::list<Takt*>& getTakts() const {
		return takts;
	}
	void clear();
	LinearSystem(Fraction duration);
	bool isFull() const{ return current->isEmpty(); }
	bool addSymbol(MusicalSymbol* symbol);
	void disconect();
	~LinearSystem();
	};

