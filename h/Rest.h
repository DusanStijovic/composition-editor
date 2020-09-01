#pragma once
#include "MusicalSymbol.h"
class Rest :public MusicalSymbol{
public:
	Rest(Fraction duration):MusicalSymbol(duration) {};
	Rest* makeCopy() const override;
	std::string type() const override;
	std::string toString()const override;
	static Rest* getRest(MusicalSymbol* mS);
	void addSymbol(std::list<Note*>& notes) {}
	Rest* newSymbol() const{ return new Rest(this->getDuration()); }
};




