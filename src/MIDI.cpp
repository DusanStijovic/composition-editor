#include "MIDI.h"

MIDI* MIDI::midi = nullptr;

bool MIDI::setMIDI(Composition* composition, std::map<Note, int> noteToMidi) {
	this->composition = composition;
	this->noteToMidi = noteToMidi;
	return true;
}

void MIDI::getMelodyAndRythm(std::pair<std::vector<int>&, std::vector<int>&> left, std::pair<std::vector<int>&, std::vector<int>&> right)  {
	for (auto takt : *composition) {
		
		for (auto symbol : *takt.first)    {
			if (symbol->isPartOfSymbol() and !symbol->isFirstpart()) 
				continue;
			Fraction duration = symbol->getDuration();
			if (symbol->isPartOfSymbol())  {
				duration = Fraction::quarter;
			}
			if (symbol->type() == "REST")  {
				left.first.push_back(0);
				left.second.push_back((duration == Fraction::quarter) ? 2 : 1);
			}
			if (symbol->type() == "NOTE")  {
				left.first.push_back(noteToMidi[*Note::getNote(symbol)]);
				left.second.push_back((duration == Fraction::quarter) ? 2 : 1);
			}
			if (symbol->type() == "CHORD") {
				Chord* chord = Chord::getChord(symbol);
				for (auto note:chord->getNotes()) {
					left.first.push_back(noteToMidi[note]);
					left.second.push_back((duration == Fraction::quarter) ? -2 : -1);
				}
				left.second.pop_back();
				left.second.push_back((duration == Fraction::quarter) ? 2 : 1);
			}
			

		}

		for (auto symbol : *takt.second) {
			if (symbol->isPartOfSymbol() and !symbol->isFirstpart())
				continue;
			Fraction duration = symbol->getDuration();
			if (symbol->isPartOfSymbol()) {
				duration = Fraction::quarter;
			}
			if (symbol->type() == "REST") {
				right.first.push_back(0);
				right.second.push_back((duration == Fraction::quarter) ? 2 : 1);
			}
			if (symbol->type() == "NOTE") {
				right.first.push_back(noteToMidi[*Note::getNote(symbol)]);
				right.second.push_back((duration == Fraction::quarter) ? 2 : 1);
			}
			if (symbol->type() == "CHORD") {
				Chord* chord = Chord::getChord(symbol);
				for (auto note : chord->getNotes()) {
					right.first.push_back(noteToMidi[note]);
					right.second.push_back((duration == Fraction::quarter) ? -2 : -1);
				}
				right.second.pop_back();
				right.second.push_back((duration == Fraction::quarter) ? 2 : 1);
			}
		}

	}
	left.first.push_back(-1);
	left.second.push_back(-1);
	right.first.push_back(-1);
	right.second.push_back(-1);
}

bool MIDI::exportCompososition(std::string fileName) {
	smf::MidiFile outputFile;
	outputFile.absoluteTicks();
	std::vector<smf::uchar> midiEvent;
	midiEvent.resize(3);
	int tpq = 48;
	outputFile.setTicksPerQuarterNote(tpq);
	outputFile.addTrack(1);
	std::vector<int> melody, rytthm, bass, brythm;
	std::pair<std::vector<int>&, std::vector<int>&> left(melody, rytthm), right(bass, brythm);
	getMelodyAndRythm(left, right);

	int i = 0;
	int actionTime = 0;
	midiEvent[2] = 64;
	while (melody[i] >= 0) {
		if (melody[i] == 0) {
			actionTime += tpq / 2 * rytthm[i++];
			continue;
		}
		midiEvent[0] = 0x90;
		midiEvent[1] = melody[i];
		outputFile.addEvent(0, actionTime, midiEvent);
		actionTime += tpq / 2 * std::abs(rytthm[i]);
		midiEvent[0] = 0x80;
		outputFile.addEvent(0, actionTime, midiEvent);
		if (rytthm[i] < 0)
			actionTime += tpq / 2 * rytthm[i];
		i++;
	}
	i = 0;
	actionTime = 0;
	while (bass[i] >= 0) {
		if (bass[i] == 0) {
			actionTime += tpq / 2 * brythm[i++];
			continue;
		}
		midiEvent[0] = 0x90;
		midiEvent[1] = bass[i];
		outputFile.addEvent(1, actionTime, midiEvent);
		actionTime += tpq / 2 * std::abs(brythm[i]);
		midiEvent[0] = 0x80;
		outputFile.addEvent(1, actionTime, midiEvent);
		if (brythm[i] < 0)
			actionTime += tpq / 2 * brythm[i];
		i++;
	}
	outputFile.sortTracks();
	outputFile.write(fileName);
	return true;
}
