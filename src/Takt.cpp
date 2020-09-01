#include "Takt.h"
int Takt::ID = 0;
std::list<Note*> Takt::extractNotes(Takt* taktleft, Takt* taktright) {
	std::list<Note*> notes;
	auto currentL = taktleft->symbols.begin();
	auto currentR = taktright->symbols.begin();
	auto endL = taktleft->symbols.end();
	auto endR = taktright->symbols.end();
	while (currentL != endL and currentR != endR) {
		(*currentL)->addSymbol(notes);
		(*currentR)->addSymbol(notes);
		currentL++;
		currentR++;
	}
	return notes;
}
std::list<MusicalSymbol*> Takt::extractSymbols(Takt* taktLeft, Takt* taktRight)
{
	std::list<MusicalSymbol*> symbol;
	auto currentL = taktLeft->symbols.begin();
	auto currentR = taktRight->symbols.begin();
	auto endL = taktLeft->symbols.end();
	auto endR = taktRight->symbols.end();
	while (currentL != endL and currentR != endR) {
		if ((*currentL)->type() == "REST" and (*currentR)->type() == "REST") {
			symbol.push_back((*currentL)->makeCopy());
			currentL++;
			currentR++;
			continue;
		}
		if ((*currentL)->type() == "CHORD" and (*currentR)->type() == "CHORD") {
			Chord* chord = Chord::getChord((*currentL)->makeCopy());
			chord->addChord(Chord::getChord(*currentR));
			symbol.push_back(chord);
			currentL++;
			currentR++;
			continue;
		}
		if ((*currentL)->type() != "REST") {
			symbol.push_back((*currentL)->makeCopy());
		}
		if ((*currentR)->type() != "REST"){
			symbol.push_back((*currentR)->makeCopy());
		}		
		currentL++;
		currentR++;
	}
	return symbol;
}
bool Takt::addSymbol(MusicalSymbol* note)
 {
	 if (note->getDuration() + currentDuration > duration) return false;
	 currentDuration = currentDuration + note->getDuration();
	 symbols.push_back(note);
	 return true;
 }
Takt:: Choice Takt::choice() {
	std::cout << "Imate sledece mogucnosti!\n";
	std::cout << "0.Povratak na takt.\n";
	std::cout << "1.Prelazak na sledecu notu\n";
	std::cout << "2.Povratak na prethodnu notu\n";
	std::cout << "3.Menjanje oktave ili visine note\n";
	std::cout << "4.Dodavanje ili uklanjanje povisilice\n";
	switch (readOption(0,4)) {
	case 0:
		return Choice::BACKFROMTAKT;
	case 1:
		return Choice::NOTEFOWARD;
	case 2:
		return Choice::NOTEBACK;
	case 3:
		return Choice::CHANGEPITCH;
	case 4:
		return Choice::CHANGESHARPNES;
	}
}
Takt::ChangePitchChoice Takt::changePitchChoice() {
	std::cout << "Izabrali ste da promenite visinu ili oktavu note!\n";
	std::cout << "Imate SLedeci izbor:\n";
	std::cout << "0.Nazad na opcije za note\n";
	std::cout << "1.Promena oktave\n";
	std::cout << "2.Promena visine\n";
		switch (readOption(0,2)) {
		case 0:
			return Takt::ChangePitchChoice::BACK;
		case 1:
			return Takt::ChangePitchChoice::CHANGEOCTAVE;
		case 2:
			return Takt::ChangePitchChoice::CHANGESTEP;
		}
}
std::pair<std::string, std::string> Takt::toString(Takt& takt1, Takt& takt2) {
	auto begin1 = takt1.getsSymbols().begin();
	auto begin2 = takt2.getsSymbols().begin();
	auto end1 = takt1.getSymbols().end();
	auto end2 = takt2.getSymbols().end();
	std::string takt1Description, takt2Desctiption;
	while (begin1 != end1 and begin2 != end2) {
		std::string description1 = (*begin1)->toString();
		std::string description2 = (*begin2)->toString();
		while (description1.size() < description2.size()) description1 += " ";
		while (description2.size() < description1.size()) description2 += " ";
		takt1Description += description1;
		takt2Desctiption += description2;
		begin1++;
		begin2++;
	}
	return std::pair<std::string, std::string>(takt1Description, takt2Desctiption);
}
void Takt::iterateTakt(Takt* taktLeft, Takt* taktRight) {
	std::list<Note*> taktsNote = Takt::extractNotes(taktLeft, taktRight);
	auto current = taktsNote.begin(), beginning = taktsNote.begin();
	auto end = taktsNote.end();
	end--;
	bool finished = false, stay = true;
	std::cout << "Izabrali ste iteriraanje kroz note takta!\n";
	int number = 1;
	while (!finished) {
		std::cout << "Nalazite se na noti broj: " << number << std::endl;
		if ((*current)->isPartOfSymbol()) std::cout << "Note je deo druge note, promena na njoj ce se oslikati na drugi deo note!\n";
		if ((*current)->isPartOfChord()) std::cout << "Nota je deo akorda!\n";
		if ((*current)->isFirstInChord()) std::cout << "Ovo je pocetak akorda!\n";
		std::cout << "Nota je:\n" << (*current)->toString()<<std::endl;
		Takt::Choice choice = Takt::choice();
		system("cls");
		switch (choice) {
		case Takt::Choice::NOTEFOWARD:
			if (current == end) {
				std::cout << "Nalazite se na  poslednjoj noti, ne mozete preci na sledecu!\n";
				break;
			}	
		current++;
		number++;		
		break;
		case Takt::Choice::NOTEBACK:
			if (current == beginning) {
				std::cout << "Nalazite se na prvoj noti, ne mozete preci na prethodnu!\n";

				break;
			}
			current--;
			number--;
			break;
		case Takt::Choice::CHANGEPITCH:
			while (stay) {
				std::cout << std::endl << "Nota je:\n" << (*current)->toString() << std::endl;
				Takt::ChangePitchChoice whatToChange = Takt::changePitchChoice();
				system("cls");
				switch (whatToChange) {
				case Takt::ChangePitchChoice::CHANGEOCTAVE:
					(*current)->changeOctave();
					break;
				case Takt::ChangePitchChoice::CHANGESTEP:
					(*current)->changeStep();
					break;
				case Takt::ChangePitchChoice::BACK:
					stay = false;
				}
				
			}
			stay = true;
			break;
		case Takt::Choice::CHANGESHARPNES:
			(*current)->changeSharpnes();
			break;
		case Takt::Choice::BACKFROMTAKT:
			return;
		}
		
	}



}
Takt::~Takt() {
	for (auto& symbol : symbols) {
		delete symbol;
		symbol = nullptr;
	}

}
