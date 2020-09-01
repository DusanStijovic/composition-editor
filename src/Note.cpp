#include "Note.h"

Note::Note(Octave octave, Pitch pitch, Fraction duration) :MusicalSymbol(duration) {
	this->octave = octave;
	this->pitch = pitch;
}
Note::Note(Note* note, Fraction duration) : Note(*note) {
	this->setDuration(duration);
}
bool Note::addSharp() {
	if (sharp) return false;
	sharp = true;
	return true;
}
Note::Note(std::string description) :MusicalSymbol(Fraction::quarter) {
	octave = getOctave(std::stoi(std::string(1, description[2])));
	pitch = Note::getPitch(toupper(description[0]));
	if (description[1] == '#')
		sharp = true;
}
Note::Pitch Note::getPitch(char pitch) {
	switch (pitch) {
	case 'A':
		return Pitch::A;
	case 'B':
		return Pitch::B;
	case 'C':
		return Pitch::C;
	case 'D':
		return Pitch::D;
	case 'E':
		return Pitch::E;
	case 'F':
		return Pitch::F;
	case 'G':
		return Pitch::G;
	default:
		return Pitch::UNDEFINEDP;
	};

}
Note::Octave Note::getOctave(int octave) {
	switch (octave) {
	case 2:
		return Octave::TWO;
	case 3:
		return Octave::THREE;
	case 4:
		return Octave::FOUR;
	case 5:
		return Octave::FIVE;
	case 6:
		return Octave::SIX;
	default:
		return Octave::UNDEFINEDO;
	}
}
char Note::getPitchC() const{
	switch (this->pitch) {
	case  Pitch::A:
		return 'A';
	case Pitch::B :
		return 'B';
	case  Pitch::C :
		return 'C';
	case  Pitch::D :
		return 'D';
	case  Pitch::E:
		return 'E';
	case Pitch::F:
		return 'F';
	case Pitch::G:
		return 'G';
	default:
		return '0';
	};
}
int Note::getOctaveI()const
{
	switch (this->octave) {
	case Octave::TWO :
		return 2;
	case  Octave::THREE :
		return 3;
	case Octave::FOUR :
		return 4;
	case Octave::FIVE :
		return 5;
	case Octave::SIX :
		return 6;
	default:
		return 0;
	}
}
Note* Note::makeCopy() const{
	return new Note(*this);
}
std::string Note::type() const{ return "NOTE"; }
std::string Note::toString()const {
	std::string noteDescription = "(";
	if (getDuration() == Fraction::eight) {
		noteDescription += tolower(getPitchC());
	}
	else
		noteDescription += toupper(getPitchC());
	if (sharp) {
		noteDescription += "#";
	}
	else
		noteDescription += " ";
	noteDescription += std::to_string(getOctaveI());
	return noteDescription += ")";

}
Note* Note::getNote(MusicalSymbol* mS) {
	if (mS->type() == "NOTE")
		return dynamic_cast<Note*>(mS);
	else
		return nullptr;
}
void Note::changeSharpnes() {
	std::cout << "Izabrali ste opciju promena povvisilice note\n";
	std::cout << "Imate slede opcije:\n";
	std::cout << "0.Nazad\n";
	std::cout << "1.Dodati povisilicu.\n";
	std::cout << "2.Ukloniti povisilicu.\n";
	int choice = readOption(0,2);
	system("cls");
	switch(choice){
	case 1:
		sharp = true;
		if(pair) pair->sharp = true;
		std::cout << "Povisilica je uspesno dodata!\n";
		break;
	case 2:
		sharp = false;
		if(pair) pair->sharp = false;
		std::cout << "Povisilica je uspesno uklonjena!\n";
	}
	return;
}
void Note::changeOctave() {
	std::cout << "Izabrali ste promenu oktave note\n";
	std::cout << "Unesite novu oktavu note kao broj izmedju 2 i 6: ";
	int octave = readOption(2, 6);
	this->octave = getOctave(octave);
	if(pair) pair->octave = this->octave;
}
void Note::changeStep() {
	std::cout << "izabrali ste opciju promene visine note:";
	std::cout << "Unesite jedno od slova A,B,C,D,E,F,G(moze i kao mala):\n";
	if (sharp) std::cout << "Ne mogu slova B i E\n";
	std::set<char> choices({ 'A', 'B', 'C',  'D', 'E', 'F', 'G' });
	std::string step;
	do {
		try {
			std::cin >> step;
			if(sharp and step.size() == 1 and toupper(step[0]) == 'E' or toupper(step[0]) == 'B') throw std::invalid_argument("Nota je povisena, ne mozete izabrati visinu B i E.\n");
			if (choices.find(toupper(step[0])) == choices.end() or step.size()!=1) throw std::invalid_argument("Izbor za visinu note nije dobar, unesite jednu od predolozenih opcija!\n");
			break;
		}
		catch (std::invalid_argument& iA) {
			std::cout << iA.what();
		}
	} while (true);
	this->pitch = getPitch(toupper(step[0]));
	if(pair) pair->pitch = this->pitch;
}
bool Note::connectSymbols(MusicalSymbol* mS) {
	if (mS->type() != "NOTE") return false;
	Note* note = Note::getNote(mS);
	if (pair) return false;
	pair = note;
	note->pair = this;
	return true;
}
