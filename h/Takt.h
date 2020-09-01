#pragma once
#include <list>
#include <iostream>
#include "Chord.h"
class Takt {
private:
	enum class Choice { NOTEFOWARD, NOTEBACK, BACKFROMTAKT,CHANGEPITCH,CHANGESHARPNES };
	enum ChangePitchChoice{BACK,CHANGEOCTAVE, CHANGESTEP};
	std::list<MusicalSymbol*> symbols;
	Fraction duration;
	Fraction currentDuration;
	static int ID;
	int taktID = ID++;
public:
	class TaktIterator :public std::iterator<MusicalSymbol, std::bidirectional_iterator_tag> {
		std::list<MusicalSymbol*>::iterator current;
	public:
		TaktIterator(std::list<MusicalSymbol*>::iterator start) {
			current = start;
		}
		friend bool operator==(const TaktIterator& cI1, const TaktIterator& cI2) {
			return cI1.current == cI2.current;
		}
		friend bool operator!=(const TaktIterator& cI1, const  TaktIterator& cI2) {
			return cI1.current != cI2.current;
		}
		MusicalSymbol* operator*() {
			return *current;
		}
		TaktIterator operator++(int) {
			TaktIterator cI(*this);
			current++;
			return cI;
		}
		TaktIterator operator++() {
			current++;
			return *this;
		}
		TaktIterator operator--(int) {
			TaktIterator cI(*this);
			current--;
			return cI;
		}

	};
	static std::list<Note *> extractNotes(Takt* taktleft, Takt* taktright);
	static std::list<MusicalSymbol*> extractSymbols(Takt* taktLeft, Takt* taktRight);
	int getTaktID()const { return taktID; }
	bool addSymbol(MusicalSymbol* note);
	Takt(Fraction duration) : currentDuration(Fraction::zero) {	this->duration = duration;}
	void setTaktID(int id) {taktID = id;}
	bool isFull()const {	return duration == currentDuration;}
	bool isEmpty()const {return symbols.empty();}
	std::list<MusicalSymbol*>& getsSymbols() {return symbols;}
	std::list<MusicalSymbol*>& getSymbols() { return symbols; }
	Fraction getDuration() { return duration; }
	TaktIterator begin() { return TaktIterator(symbols.begin()); }
	TaktIterator end() { return TaktIterator(symbols.end()); }
	static Choice choice();
	static ChangePitchChoice changePitchChoice();
	static std::pair<std::string, std::string> toString(Takt& takt1, Takt& takt2);
	static void iterateTakt(Takt* taktLeft, Takt* taktRight);
	~Takt();
};

