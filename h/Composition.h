#pragma once
#include "LinearSystem.h"
#include "BadInputFile.h"
#include <string>
#include <fstream>
#include <regex>
#include "Rest.h"
#include <iostream>
#include <iomanip> 
#include <algorithm>
class Composition {
private:  
	LinearSystem leftHand, rightHand;
	Fraction takt;
public:
	class CompositionIterator :public std::iterator<Takt, std::bidirectional_iterator_tag> {
		std::list<Takt*>::iterator currentL, currentR;
	public:
		CompositionIterator(std::list<Takt*>::iterator left, std::list<Takt*>::iterator right) {
			currentL = left;
			currentR = right;
		}
		friend bool operator==(const CompositionIterator &cI1, const CompositionIterator& cI2) {
			return cI1.currentL == cI2.currentL and cI1.currentR == cI2.currentR;
		}
		friend bool operator!=(const CompositionIterator& cI1, const CompositionIterator& cI2) {
			return cI1.currentL != cI2.currentL or cI1.currentR != cI2.currentR;
		}
		std::pair<Takt*, Takt*> operator*() {
			return std::pair<Takt*,Takt*>(*currentL, *currentR);
		}
		CompositionIterator operator++(int) {
			CompositionIterator cI(*this);
			currentL++;
			currentR++;
			return cI;
		}
		CompositionIterator operator++() {
			currentL++;
			currentR++;
			return *this;
		}
		CompositionIterator operator--(int){
			CompositionIterator cI(*this);
			currentL--;
			currentR--;
			return cI;
		}

	};
	enum class Choice {BACKTOMAINMANU, TAKTBACK, TAKTFOWARD, GOINTAKT, NOTEBACK, NOTEFOWARD };
	LinearSystem& getRightHand() { return rightHand; }
	LinearSystem& getLeftHand() { return leftHand; }
	bool isFulLeft() { return leftHand.isFull(); }
	bool isFullRight() { return rightHand.isFull(); }
	Composition(Fraction compositionTakt);
	void changeOctaveToALL(int octave);
	void changeTakt(Fraction newTakt);
	CompositionIterator begin() { return CompositionIterator(leftHand.getTakts().begin(), rightHand.getTakts().begin()); }
	CompositionIterator end() { return CompositionIterator(leftHand.getTakts().end(), rightHand.getTakts().end()); }

	bool addMusicalSymbol(MusicalSymbol* symbol);
    auto getTaktsForLeft() { return leftHand.getTakts(); }
	auto getTaktsForRight() { return rightHand.getTakts(); }
    const std::list<Takt*> & getTaktsForLeft() const { return leftHand.getTakts(); }
	const std::list<Takt*> & getTaktsForRight() const { return rightHand.getTakts(); }
	Fraction getTakt() { return takt; }
	Choice choice();
	void iterateComposition();
	friend std::ostream& operator<<(std::ostream& os, const Composition& composition);

};

 