#pragma once
#include <map>
#include <set>
#include "BadInputFile.h"
#include <string>
#include <fstream>
#include <regex>
#include "BMP.h"
#include "MXML.h"
class Piano {
private:
    static	Piano* piano;
	std::map<Note, std::vector<unsigned char>> symbolColor;
	std::map <char, Note*> charToNote;
	std::map <Note, int> noteToMidi;
	Composition * composition = nullptr;
	bool settingsLoaded = false;
	bool exported = false;
public:
	enum class UserChoice { EXIT, LOAD_PIANO_KEYS, LOAD_COMPOSITION, PRINT_COMPOSITION, ITERATE_THROUGH_COMPOSITION, CHANGE_COMPOSITION_OCTAVE, CHANGE_COMPOSITION_TAKT, EXPORT, EXPORT_AS_MUSIXXML, EXPORT_AS_MIDI, EXPORT_AS_BMP, STARTFROMBEGINING,BACK };
	enum class Hand {LEFT, RIGHT, BOTH };
	enum class Answer { YES, NO };

	UserChoice userChoice();
	bool exportComposition();
	void clearNoteMap();
	~Piano() {
		delete composition;
		clearNoteMap();
	}
	static UserChoice loadExportMenu();
	void makeNote(char ch, Fraction duration);
	void processSymbol(std::string symbol);
	bool loadPianoKeys(std::string pianoKey);
	bool loadComposition(std::string composition);
	std::string  loadKeysMenu();
	bool sureForExit();
	std::string loadCompositionManu();
	friend int readOption(int low, int high);
	static bool sureForBeginning();
	bool loadNewComposition();
	void userManu();
	static Piano& getPiano();
};
