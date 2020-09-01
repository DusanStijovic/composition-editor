 #include "Chord.h"

bool Chord::addNote(Note note) {
	if (notes.empty() || notes.front().getDuration() == note.getDuration()) {
		note.setAsPartOfChord();
		if (notes.empty()) note.setAsFisrtPartOfChord();
		notes.push_back(note);
		return true;
	}
	return false;
}
Chord* Chord::makeCopy()const {
	return new Chord(*this);
}
void Chord::addChord(Chord * chord) {
	auto& notes = chord->getNotes();
	for (auto note : notes) {
		this->notes.push_back(note);
	}
	

}
void Chord::setDuration(Fraction duration) {
	for (auto& note : notes) {
		note.setDuration(duration);
	}
	MusicalSymbol::setDuration(duration);
}
void Chord::setSymbolAsPair() {
	MusicalSymbol::setSymbolAsPair();
	for (auto& note : notes)
		note.setSymbolAsPair();
}
void Chord::setSymbolAsFirstPair() {
	MusicalSymbol::setSymbolAsPair();
	firstPart = true;
	for (auto& note : notes)
		note.setSymbolAsFirstPair();
}
std::string Chord::toString() const{
	std::string chordDescription = "[";
	for (auto note : notes) {
		chordDescription += note.toString();
	}
	return chordDescription + "]";
}
Chord* Chord::getChord(MusicalSymbol* mS) {
	if (mS->type() == "CHORD")
		return dynamic_cast<Chord*>(mS);
	else
		return nullptr;
}
void Chord::addSymbol(std::list<Note*>& list) {
	for (Note& note : notes)
		list.push_back(&note);
}
bool Chord::connectSymbols(MusicalSymbol* mS) {
	if (mS->type() != "CHORD") return false;
	Chord* chord = Chord::getChord(mS);
	int position = 0;
	for (auto& note : notes)
		note.connectSymbols(&chord->notes.at(position++));
	return true;
}
Chord* Chord::newSymbol()const {
	Chord* chord = new Chord(this->getDuration());
	for (auto note : notes) {
		chord->addNote(Note(note.getOctave(), note.getPitch(),note.getDuration()));
	}
	return chord;
}

