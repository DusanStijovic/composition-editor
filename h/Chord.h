#pragma once
#include "Note.h"
#include <vector>
#include <list>
class Chord :public MusicalSymbol{
private:
	std::vector <Note> notes;

public:
	Chord(Fraction duration) :MusicalSymbol(duration) {}
	bool addNote(Note note);
	bool isEmpty()const { return notes.empty(); }
	Chord* makeCopy() const override;
	auto & getNotes() const { return notes; }
	void setDuration(Fraction duration);
	~Chord() {};
	void  setSymbolAsPair()override;
	std::string type()const  override{ return "CHORD"; }
	void  setSymbolAsFirstPair() override;
	std::string toString()const override;
	static Chord* getChord(MusicalSymbol* mS) ;
	void addSymbol(std::list<Note*>& list);
	bool connectSymbols(MusicalSymbol* mS);
	Chord* newSymbol() const;
	void addChord(Chord* chord);
};

