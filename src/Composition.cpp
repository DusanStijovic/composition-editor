#include "Composition.h"

Composition::Composition(Fraction compositionTakt) :leftHand(compositionTakt), rightHand(compositionTakt) {
	this->takt = compositionTakt;
}
void Composition::changeOctaveToALL(int octave) {
	if (octave == 0) return;
	for (auto takt : *this) {
		std::list<Note*> notes = Takt::extractNotes(takt.first, takt.second);
		std::for_each(notes.begin(), notes.end(), [octave](Note * note) {
			int noteOctave = note->getOctaveI();
			noteOctave += octave;
			if (octave > 0) {
				if (noteOctave > Note::Octave::SIX) noteOctave = Note::Octave::SIX;
			}
			else {
				if (noteOctave < Note::Octave::TWO) noteOctave = Note::Octave::TWO;
			}
			note->setOctave(noteOctave);
			});
	}
}
void Composition::changeTakt(Fraction newTakt) {
	LinearSystem left(newTakt), right(newTakt);
	std::for_each(this->begin(), this->end(), [&left, &right](std::pair<Takt*, Takt*> takt) {
		std::for_each(takt.first->begin(), takt.first->end(), [&left](MusicalSymbol * mS) {
			if (mS->isPartOfSymbol() and !mS->isFirstpart()) return;
			MusicalSymbol* newmS = mS->newSymbol();
			if (mS->isFirstpart())
				newmS->setDuration(Fraction::quarter);
			left.addSymbol(newmS);
			});
		std::for_each(takt.second->begin(), takt.second->end(), [&right](MusicalSymbol * mS) {
			if (mS->isPartOfSymbol() and !mS->isFirstpart()) return;
			MusicalSymbol* newmS = mS->newSymbol();
			if (mS->isFirstpart())
				newmS->setDuration(Fraction::quarter);
			right.addSymbol(newmS);
			});
		});
	leftHand = left;
	rightHand = right;
	while (!leftHand.isFull()) leftHand.addSymbol(new Rest(Fraction::eight));
	while (!rightHand.isFull()) rightHand.addSymbol(new Rest(Fraction::eight));

	left.disconect();
	right.disconect();
	takt = newTakt;
}
bool Composition::addMusicalSymbol(MusicalSymbol* symbol) {
	leftHand.addSymbol(symbol);
	rightHand.addSymbol(symbol->makeCopy());
	return true;
}
Composition::Choice Composition::choice() {
	std::cout << "Imate sledece mogucnosti:\n";
	std::cout << "0.Povratak na  meni.\n";
	std::cout << "1.Prelazak na sledeci takt.\n";
	std::cout << "2.Povratak na prethodni takt.\n";
	std::cout << "3.Iteriranje kroz note takta.\n";
	switch (readOption(0, 3)) {
	case 0:
		return Choice::BACKTOMAINMANU;
	case 1:
		return Choice::TAKTFOWARD;
	case 2:
		return Choice::TAKTBACK;
	case 3:
		return Choice::GOINTAKT;
	}

}
void Composition::iterateComposition() {
	auto current = begin();
	CompositionIterator end = this->end();
	auto beginning = begin();
	end--;
	
	bool finished = false;
	std::cout << "Izabrali ste iteriranje kroz taktove kompozicije!\n";

	while (!finished) {
		std::cout << "Nalazite se na taktu:" << (*current).first->getTaktID() << std::endl;
		std::cout << "Takt izgleda ovako:\n";
		std::pair<std::string, std::string> description = Takt::toString(*(*current).first,*(*current).second);
		std::cout << description.second << std::endl << description.first << std::endl;
		Choice choice = this->choice();
		std::cout << std::setfill('_') << std::setw(40) << "\n";
		system("cls");
		switch (choice) {
			
		case Choice::TAKTBACK:
			if (current == beginning) {//dovoljno je jedan uslov, posto imamo isto taktova u obe ruke.
				std::cout << "Nalazite se na prvom taktu, ne mozete preci na prethodni takt!\n";
				break;
			}
			current--;
			break;
		case Choice::TAKTFOWARD:
			if (current == end) {//dovoljno je jedan uslov, posto imamo isto taktova u obe ruke.
				std::cout << "Nalazite se na poslednjem taktu taktu, ne mozete preci na sledeci takt!\n";
				break;
			}
			current++;
			break;
		case Choice::GOINTAKT:
			if (choice == Choice::GOINTAKT) {
				Takt::iterateTakt((*current).first, (*current).second);
			}
			break;
		case Choice::BACKTOMAINMANU:
			return;
		}

	}
}
std::ostream& operator<<(std::ostream & os, const Composition & composition) {
		std::string leftHand = "", rightHand = "";
		auto beginL = composition.leftHand.getTakts().begin(), beginR = composition.rightHand.getTakts().begin();
		auto endL = composition.leftHand.getTakts().end(), endR = composition.rightHand.getTakts().end();
		int numberOfTaktsInLine = 3, currentNumberOfTaktsInLine = 0;
		if (composition.leftHand.getTakts().size() < numberOfTaktsInLine) numberOfTaktsInLine = composition.leftHand.getTakts().size();
		std::pair<std::string, std::string> twoTakt;
		while (beginL != endL and beginR != endR) {
			twoTakt = Takt::toString(**beginL, **beginR);
			leftHand += twoTakt.first + "|";
			rightHand += twoTakt.second + "|";
			currentNumberOfTaktsInLine++;
			if (currentNumberOfTaktsInLine == numberOfTaktsInLine) {
				os << rightHand << std::endl;
				os << leftHand << std::endl;
				rightHand = "";
				leftHand = "";
				os << std::setfill('_') << std::setw(rightHand.size()) << "" << std::endl;
				currentNumberOfTaktsInLine = 0;
			}
			beginL++;
			beginR++;
		}
		std::cout << std::endl;
		return os;
	}

