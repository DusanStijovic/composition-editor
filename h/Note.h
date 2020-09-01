#pragma once
#include "MusicalSymbol.h"
//#include "Piano.h"
#include <iostream>
#include <set>
#include <vector>
extern int readOption(int low, int high);
class Note :public MusicalSymbol{
public:
	
	enum  Octave {
		UNDEFINEDO, TWO = 2, THREE, FOUR, FIVE, SIX
	};
	enum  Pitch { UNDEFINEDP, A, B, C, D, E, F, G };
	Note(Octave octave, Pitch pitch, Fraction duration = Fraction::one);
	Note(Note* note, Fraction duration);
	bool addSharp();
	bool isSharp() const {
		return sharp;
	}
	Note(std::string description);
	static Pitch getPitch(char pitch);
	static Octave getOctave(int octave);
	char getPitchC() const;
	int getOctaveI() const;
	Octave getOctave() const { return octave; }
	Pitch getPitch() const { return pitch; }
	Note* makeCopy() const override;
	void setAsPartOfChord() { partOfChord = true; }
	bool isPartOfChord()const { return partOfChord; }
	bool isFirstInChord() const{ return firstPartOfChord; }
	void setAsFisrtPartOfChord() { firstPartOfChord = true; }
	void addSymbol(std::list<Note*>& notes) override{
		notes.push_back(this);
	}
	std::string type() const override;
	std::string toString()const override;
	static Note* getNote(MusicalSymbol* mS);
	void changeSharpnes();
	void changeOctave();
	void changeStep();
	void setOctave(int octave) { this->octave = getOctave(octave); }
	bool connectSymbols(MusicalSymbol* mS)override;
	Note* newSymbol() const override { return new Note(this->getOctave(),this->getPitch(),this->getDuration());}
	friend bool operator<(const Note& note1, const Note& note2) {
		std::string note1Description = std::string(1, note1.getPitchC()) + (note1.sharp ? "#" : "") + std::to_string(note1.getOctaveI());
		std::string note2Description = std::string(1, note2.getPitchC()) + (note2.sharp ? "#" : "") + std::to_string(note2.getOctaveI());
		return note1Description < note2Description;
	}
private:
	Octave octave;
	Pitch pitch;
	bool sharp = false;
	bool partOfChord = false;
	bool firstPartOfChord = false;
	Note* pair = nullptr;
};

