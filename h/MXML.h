#ifndef  _MXML_H
#define _MXML_H
#include "Formatter.h"
#include <string>
#include "Composition.h"
#include "Note.h"
#include "MusicalSymbol.h"
#include "Chord.h"

class MXML :public Formatter{
	std::string outputFile = "";
private:
	enum class Choice{NOTHING,STARTLEFTPART, STARTRIGHTPART};
	MXML();
	static MXML* mxml;
	Composition* composition = nullptr;
	void startTag();
	void startMeasureTag();
	void endMeasureTag();
	void startAtrrtibutesTag();
	void endAttributesTag();
	void startNoteTag();
	void endNoteTag();
	void startPitchTag();
	void endPitchTag();
	void startDurationTag();
	void endDurattionTag();
	void startOctaveTag();
	void endOctaveTag();
	void startStepTag();
	void endStepTag();
	void startAlterTag();
	void endAlterTag();
	void addAlterTag(Note note);
	void addOctaveTag(int octave);
	void addSteptag(int step);
	void addDurationTag(Fraction duration);
	void addPitchTag(Note);
	void addAtributesTag(Fraction takt, std::string sign, int line);
	void addMeasureTag(Takt *takt,Choice choice);
	void addTieTag(MusicalSymbol * ms);
	void addChordTag(Note*);
	void addRestTag(Rest*);
	void startPartTagRight();
	void startPartTagLeft();
	void endPartTag();
	void startTimeTag();
	void endTimeTag();
	void addBeatsTag(int);
	void addBitTypeTag(int);
	void startClefTag();
	void endClefTag();
	void addSignTag(std::string);
	void addLineTag(int);
	void addDivisionTag(int);
	void addNoteTag(Note* note);
	void addChord(Chord* chord);
public:
	static MXML* getMXML();
	bool exportCompososition(std::string fileName);
	void setCompostition(Composition* composition);
};
#endif // ! _MXML_H
