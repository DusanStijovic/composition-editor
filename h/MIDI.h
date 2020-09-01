#pragma once
#include "MidiFile.h"
#include "Formatter.h"
#include <iostream>
#include "Note.h"
#include <map>
class MIDI :public Formatter{
private:
	static MIDI* midi;
	std::map<Note, int> noteToMidi;
	MIDI() { };
public:
	static MIDI* getMIDI() {
		if (midi == nullptr) {
			midi = new MIDI();
		}
		return midi;
	}
	bool setMIDI(Composition* composition, std::map<Note, int> noteToMidi);
	MIDI(Composition *composition, std::map<Note, int> noteToMidi1):Formatter(composition),noteToMidi(noteToMidi1) {};
	void getMelodyAndRythm(std::pair<std::vector<int>&, std::vector<int>&>  left, std::pair<std::vector<int>&, std::vector<int>&>  right);
	bool exportCompososition(std::string fileName);
	~MIDI() {};
};














