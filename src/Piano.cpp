// Piano.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Piano.h"
#include "Composition.h"
#include "Chord.h"
#include "MIDI.h"
#include "OutOfRange.h"
#include "ExtensionNotDetected.h"
#include "NotDetectedFileName.h"
#include "BadSettingsFile.h"
#include "ForbiddenCharacters.h"
#include "BadCompositionFile.h"
#include "InputFileEmpty.h"
Piano * Piano::piano = nullptr;
int main()
{
	Piano::getPiano().userManu();
	return 1;

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
int readOption(int low, int high) {
	std::string checkChoice;
	do {
		try {
			std::cout << "Izbor: ";
			std::cin >> checkChoice;
			if (checkChoice.size() != 1) throw std::invalid_argument("Treba uneti jedan broj");
			int option = std::stoi(checkChoice);
			if (option < low or option > high) throw new OutOfRange(low, high);
			return option;
		}
		catch (std::invalid_argument& iA) {
			std::cout << "Uneli ste nevalidne podatke, unesite jedan broj!\n";
		}
		catch (OutOfRange* outOf) {
			std::string description = outOf->message();
			std::cout << description;
			delete outOf;
		}
		catch (std::out_of_range& outOf) {
			std::cout << "Uneli ste preveliki broj!\n";
		}
	} while (true);
}
std::string readFileName(std::string format) {
	std::string fileName;
	do {
		try {
			std::cout << "Ime fajla: ";
			std::cin >> fileName;
			if (fileName.size() <= format.length()) throw new NotDetectedFileName(format.length() + 1);
			if (fileName.substr(fileName.size() - format.length()) != format) throw new ExtensionNotDetected(format);
			return fileName;
		}
		catch (ExtensionNotDetected* extension) {
			std::cout << extension->message();
		}
		catch (NotDetectedFileName* notFileName) {
			std::cout << notFileName->message();
		}
	} while (true);
}
bool Piano::sureForExit() {
	if (!exported and composition) {
		std::cout << "\nDa li ste sigurni da zelite da napustite program, posto niste eksportovali kompoziciju ni u jedan fromat?\n";
		std::cout << "1.Da hocu da napustim program.\n";
		std::cout << "2.Ipak necu da napustim program.\n";
		return readOption(1, 2) == 1 ? true : false;
	}
	else
		return true;
}
std::pair<int, int> loadFraction() {
	std::regex fraction("([^/]+)/([^ ]+)");
	std::smatch result;
	std::string takt;
	int num = 3, den = 4;
	do {
		std::cin >> takt;
		if (std::regex_match(takt, result, fraction)) {
			try {
				num = std::stoi(result.str(1));
				den = std::stoi(result.str(2));
				if (num > den) throw std::invalid_argument("Nevalidni argumenti, brojilac je vec iod imenioca.\n");
				if (den != 8 and den != 4) throw std::invalid_argument("Delioc treba da bude 4 ili 8.\n");
				if (num == 0) throw std::invalid_argument("Imenioc ne moze biti 0.\n");  
				break;
			}
			catch (const std::invalid_argument& ia) {
				std::cout << ia.what();
			}
			catch (const std::out_of_range & oor) {
				std::cout << "Preveliki broj!\nTakt:";
			}
		}
		else {
			std::cout << "Niste uneli takt u trazenom formatu!\n";
		}
		std::cout << "Takt: ";
	} while (true);
	return std::pair<int, int>(num, den);
}
std::string Piano::loadCompositionManu() {
	std::cout << "\nUneli ste opciju ucitavanja kompozicije!\n";
	std::cout << "Unesite takt kompozicije u formatu a/b!\n";
	std::cout << "Takt: ";
	std::pair<int, int>takt(loadFraction());
	this->composition = new Composition(Fraction(takt.second,takt.first));
	std::cout << "Unesite ime fajla u kome se nalazi kompozicija u formatu imefajla.txt!\n";
	return readFileName(".txt");
}
bool Piano::sureForBeginning() {
	std::cout << "Niste sacuvali trenutnu kompoziciju da li ste sigurni da zelite da restartuje klavir\n";
	std::cout << "1.Da hocu da restartujem klavir.\n";
	std::cout << "2.Ipak necu da restartujem klavir.\n";
	return readOption(1, 2) == 1 ? true : false;
}
bool Piano::exportComposition(){
	std::string fileName = "";
	switch (loadExportMenu()){
	case UserChoice::EXPORT_AS_MIDI:
		MIDI::getMIDI()->setMIDI(composition, noteToMidi);
		std::cout << "Izabrali ste eksportovanje kao MIDI fajl\n";
		std::cout << "Unesite ime fajla u formatu imeFajla.mid\n";
		fileName = readFileName(".mid");
		MIDI::getMIDI()->exportCompososition(fileName);
		fileName = "";
		break;
	case UserChoice::EXPORT_AS_MUSIXXML:
		MXML::getMXML()->setCompostition(composition);
		std::cout << "Izabrali ste eksportovanje kao Musicxml fajl\n";
		std::cout << "Unesite ime fajla u formatu imeFajla.musicxml\n";
		fileName = readFileName(".musicxml");
		MXML::getMXML()->exportCompososition(fileName);
		fileName = "";
		break;
	case UserChoice::EXPORT_AS_BMP:
		BMP::getBMP()->setComposition(composition);
		std::cout << "Izabrali ste eksportovanje kao BMP fajl\n";
		std::cout << "Unesite ime fajla u formatu imeFajla.bmp\n";
		fileName = readFileName(".bmp");
		BMP::getBMP()->exportCompososition(fileName);
		fileName = "";
		break;
	default:
		break;
	}
	
	return false;
}
void Piano::clearNoteMap() {
	for (auto& pair : charToNote) {
		delete pair.second;
		pair.second = nullptr;
	}

}
Piano::UserChoice Piano::loadExportMenu() {
	std::cout << "Izabrali ste opciju eksportovanja kompozicije\n";
	std::cout << "Imate sledece opcije:\n";
	std::cout << "0.Nazad na glavni meni.\n";
	std::cout << "1.Eksportovanje kao MusixXML fajl.\n";
	std::cout << "2.Eksportovanje kao MIDI fajl.\n";
	std::cout << "3.Eksportovanje kao BMP fajl.\n";
	std::string choice;

	switch (readOption(0,3)) {
	case 0:
		return UserChoice::BACK;
	case 1:
		return UserChoice::EXPORT_AS_MUSIXXML;
	case 2:
		return UserChoice::EXPORT_AS_MIDI;
	case 3:
		return UserChoice::EXPORT_AS_BMP;
	}
	return UserChoice::BACK;
}
bool Piano::loadNewComposition() {
	std::cout << "Niste sacuvali trenutnu kompoziciju da li ste sigurni da zelite da ucitate novu?\n";
	std::cout << "1.Da hocu da ucitam novu\n";
	std::cout << "2.Ipak necu da ucitam novu\n";
	return readOption(1,2);
}
int octaveChoice() {
	std::cout << "Izabralali ste da promenite oktavu svake note u kompoziciji:\n";
	std::cout << "Imate sledeci izbor:\n";
	std::cout << "0.Nazad\n";
	std::cout << "1.Pomeriti za zadati broj oktava vise.\n";
	std::cout << "2.Pomeriti za zadati broj oktava nize.\n";
	int choice = readOption(0,2);
	switch 	(choice) {
	case 0:
		return 0;
	case 1:
		std::cout << "Izabrali se da pomerite kompoziciju za zadati brok oktava vise.\n";
		std::cout << "Oktave se krecu od 2 do 6 ako unesete neki broj veci od 4, sve note ce se pomeriti za 4 oktava.\n";
		std::cout << "Ako neka nota ne moze da se pomeri zadati broj oktava ona ce se pomeriti na sestu oktavu.\n";
		break;
	case 2:
		std::cout << "Izabrali ste da pomerite kompozciju za zadati broj oktava nize.\n";
		std::cout << "Oktave se krecu od 2 do 6 ako unesete neki broj veci od 4, sve note ce se pomeriti za 4 oktave.\n";
		std::cout << "Ako neka nota ne moze da se pomeri zadati broj oktava ona ce se pomeriti na drugu oktavu.\n";
	}

	std::cout << "Izbor: ";
	int value;
	std::cin >> value;
	if (!choice) value = -value;
	return value;
}
Fraction taktChoice() {
	std::cout << "izabrali ste promenu takta kompozicije.\n";
	std::cout << "Unesite novi takt u formatu a/b.\n";
	std::cout << "Novi takt: ";
	std::pair<int, int> newTakt = loadFraction();
	return Fraction(newTakt.second, newTakt.first);
}
void Piano::userManu() {
	while (true) {
		try {
			UserChoice option = userChoice();
			system("cls");
			switch (option) {			
			case UserChoice::EXIT:
				if (sureForExit()) {
					std::cout << "Zao nam je sto idete, vratite se sto pre!\n";
					return;
				}
				else break;
			case UserChoice::LOAD_PIANO_KEYS:
				if (settingsLoaded) {
					std::cout << "Podesavanja su vec ucitana.\n";
					std::cout << "Ako zelite nova restartujte klavir!\n";
					break;
				}
				Piano::getPiano().loadPianoKeys(loadKeysMenu());
				std::cout << "Podesavanja klavira su uspesno ucitana!\n";
				settingsLoaded = true;
				break;
			case UserChoice::LOAD_COMPOSITION:
				if (!settingsLoaded) {
					std::cout << "Niste ucitali podesavanja klavira!\n";
					break;
				}
				if (!exported and composition) {
					if (!loadNewComposition())
						break;
				}
				delete composition;
				composition = nullptr;
				loadComposition(loadCompositionManu());
				exported = false;
				std::cout << "Kompozicija je uspesno ucitana!\n";
				break;
			case UserChoice::PRINT_COMPOSITION:
				if (!composition) {
					std::cout << "Niste ucitali kompoziciju!\n";
					break;
				}
				std::cout << "Kompozicija:\n";
				std::cout << *composition;
				break;
			case UserChoice::ITERATE_THROUGH_COMPOSITION:
				if (!composition) {
					std::cout << "Niste ucitali kompoziciju!\n";
					break;
				}
				composition->iterateComposition();
				break;
			case UserChoice::EXPORT:
				if (!composition) {
					std::cout << "Niste ucitali kompoziciju!\n";
					break;
				}
				this->exportComposition();
				exported = true;
				break;
			case UserChoice::CHANGE_COMPOSITION_OCTAVE:
				if (!composition) {
					std::cout << "Niste ucitali kompoziciju!\n";
					break;
				}
				composition->changeOctaveToALL(octaveChoice());
				break;
			case UserChoice::CHANGE_COMPOSITION_TAKT:
				if (!composition) {
					std::cout << "Niste ucitali kompoziciju!\n";
					break;
				}
				composition->changeTakt(taktChoice());
				break;

			case UserChoice::STARTFROMBEGINING:
				if (!settingsLoaded) {
					std::cout << "Niste ucitavali podesavanja, nema sta da se restartuje!\n";
					break;
				}
				if (!exported and composition)
					if (!sureForBeginning()) break;
				delete composition;
				composition = nullptr;
				clearNoteMap();
				charToNote.clear();
				noteToMidi.clear();
				settingsLoaded = false;
				exported = false;
				std::cout << "Podesavanja su resetovana!\n";
				break;


			}
			std::cout << "Pritisnite enter da biste nastavili!";
			int k = std::cin.get();
			do{	
				if (std::cin.get() == '\n')
					break;
					
			} while (true);
			system("cls");
		}
		catch (BadSettingsFile* badSettings) {
			std::cout << badSettings->message();
			clearNoteMap();
			charToNote.clear();
			delete badSettings;
		}
		catch (ForbiddenCharacters* forbidden) {
			std::cout << forbidden->message();
			clearNoteMap();
			charToNote.clear();
			delete forbidden;
		}
		catch (BadCompositionFile* badCompositionFile) {
			std::cout << badCompositionFile->message();
			delete badCompositionFile;
			delete composition;
			composition = nullptr;
		}
		catch (BadInputFile* badInputFile) {
			std::cout << badInputFile->message();
			delete composition;
			composition = nullptr;
			delete badInputFile;
		}
		catch (InputFileEmpty* inputFileEmpty) {
			std::cout << inputFileEmpty->message();
			delete composition;
			composition = nullptr;
			delete inputFileEmpty;
		}

	}

}
Piano& Piano::getPiano() {
	if (!piano) {
		piano = new Piano();
	}
	return *piano;
}
Piano::UserChoice Piano::userChoice() {
	std::cout << "___________________________________________________________________________\n";
	std::cout << "Dobro dosli u virtuelni klavir!\n";
	std::cout << "Imate sledece opcije:\n";
	std::cout << "0.Izlaz\n";
	std::cout << "1.Ucitavanje podesavanja klavira.\n";
	std::cout << "2.Ucitavanje kompozicije.\n";
	std::cout << "3.Ispis kompozicije.\n";
	std::cout << "4.Iteriranje kroz kompoziciju.\n";
	std::cout << "5.Pomeranje kompozicije po oktavama.\n";
	std::cout << "6.Promena takta kompozicije.\n";
	std::cout << "7.Eksportovanje kompozicije.\n";
	std::cout << "8.Restartuj klavir.\n";

	switch (readOption(0, 8)) {
	case 0:
		return UserChoice::EXIT;
	case 1:
		return UserChoice::LOAD_PIANO_KEYS;
	case 2:
		return UserChoice::LOAD_COMPOSITION;
	case 3:
		return UserChoice::PRINT_COMPOSITION;
	case 4:
		return UserChoice::ITERATE_THROUGH_COMPOSITION;
	case 5:
		return UserChoice::CHANGE_COMPOSITION_OCTAVE;
	case 6:
		return UserChoice::CHANGE_COMPOSITION_TAKT;
	case 7:
		return UserChoice::EXPORT;
	case 8:
		return UserChoice::STARTFROMBEGINING;
	default:
		return UserChoice::EXIT;
	}
}
 void Piano::makeNote(char ch, Fraction duration){
	 if (charToNote.find(ch) == charToNote.end()) throw  new BadCompositionFile();
	 Note* note = new Note(charToNote[ch], duration);
	 std::vector<unsigned char> color; color.resize(3);
	 color[0] = color[1] = color[2] = 0xFF;
	 if (note->getOctave()> Note::Octave::THREE) {
		 composition->getRightHand().addSymbol(note);
		 composition->getLeftHand().addSymbol(new Rest(note->getDuration()));
	 }
	 else {
		 composition->getLeftHand().addSymbol(note);
		 composition->getRightHand().addSymbol(new Rest(note->getDuration()));
	 }


 }
 void Piano::processSymbol(std::string symbol) {
	 if (symbol == "|") {
		 composition->addMusicalSymbol(new Rest(Fraction::quarter));
		 return;
	 }
	 if (symbol == "_") {
		 composition->addMusicalSymbol(new Rest(Fraction::eight));
		 return;
	 }
	 if (symbol[0] != '[') {
		 for (auto ch : symbol) {
			 makeNote(ch, Fraction::quarter);
		 }
		 return;
	 }
	 if (symbol.find(" ") != std::string::npos or symbol.length() == 3) {
		 for (int i = 1; i < symbol.length() - 1; i += 2) {
			 makeNote(symbol[i], Fraction::eight);
		 }
		 return;
	 }
	 Chord* chordLeft = new Chord(Fraction::quarter);
	 Chord* chordRight = new Chord(Fraction::quarter);
	 for (int i = 1; i < symbol.length() - 1; i++) {
		 if (charToNote.find(symbol[i]) == charToNote.end()) throw new BadCompositionFile() ;
		 Note note = Note(charToNote[symbol[i]], Fraction::quarter);
		 if (note.getOctave() > Note::Octave::THREE) {
			chordRight->addNote(note);
		 }
		 else {
		  chordLeft->addNote(note);
		 }
	 }
	 if (!chordLeft->isEmpty()) composition->getLeftHand().addSymbol(chordLeft);
	 else {	
		 delete chordLeft;
		 composition->getLeftHand().addSymbol(new Rest(Fraction::quarter));
	 }
	 if (!chordRight->isEmpty()) composition->getRightHand().addSymbol(chordRight);
	 else {
		 delete chordRight;
		 composition->getRightHand().addSymbol(new Rest(Fraction::quarter));
	 }
 }
 bool Piano::loadPianoKeys(std::string pianoKey) {
	std::ifstream mapNotes(pianoKey); 
	std::regex readNotes("(.),([A-G])(#?)([2-6]),([0-9]*).*");
	std::string input;
	try {
		while (std::getline(mapNotes, input)) {
			std::smatch result;
			if (std::regex_match(input, result, readNotes)) {
				if (result.size() != 6) 
					throw new BadSettingsFile();
				Note::Pitch pitch = Note::getPitch(result.str(2)[0]);
				Note::Octave octave = Note::getOctave(std::stoi(result.str(4)));
				Note* note = new Note(octave, pitch);
				if (result.str(3) != "") note->addSharp();
				if (result.str(1)[0] == '[' or result.str(1)[0] == ']' or result.str(1)[0] == '|' or result.str(1)[0] == ' ') 
					throw ForbiddenCharacters();
				charToNote[result.str(1)[0]] = note;
				noteToMidi[*note] = std::stoi(result.str(5));
			}
			else 
				throw new BadSettingsFile();
		}
	}
	catch (std::invalid_argument& ia) { throw new BadSettingsFile(); }
	catch (std::out_of_range& outOf) { throw new BadSettingsFile(); }
	mapNotes.close();
	if (charToNote.empty())
		throw new InputFileEmpty();
	return true;
}
 bool Piano::loadComposition(std::string composition) {
	 std::ifstream compositionFile(composition);
	 std::regex matchAll("([^\\[]+)?(\\[[^\\]]+\\])?");
	 bool previousIsRest = true, sequenceStarted = false;
	 std::string result;
	 bool first = true, restPossible = false;
	 while (std::getline(compositionFile, result)) {
		 std::sregex_iterator begin(result.begin(), result.end(), matchAll);
		 std::sregex_iterator end;
		 while (begin != end) {
			 std::smatch onePart = *begin;
			 if (onePart.str(1) != "") {	
				 first = true;
				 restPossible = false;
				 std::regex match1("([^ ]+)?( )?");
				 std::string help = onePart.str(1);
				 std::sregex_iterator begin1(help.begin(), help.end(),match1);
				 std::sregex_iterator end1;
				 while (begin1 != end1) {
					 std::smatch another = *begin1;
					 if (another.str(1) != "") {
						 if (another.str(1) != "|" and restPossible) {
							 processSymbol("_");
						 }
						 processSymbol(another.str(1));
						 restPossible = false;
					 }
					 if (another.str(2) == " " and another.str(1) != "|") {
						 restPossible = true;
					 }
					 begin1++;
				 }
			 }
			 if (restPossible) {
				 processSymbol("_");
				 restPossible = false;
			 }
			 if (onePart.str(2) != "") {
				 processSymbol(onePart.str(2));
			 }
			 begin++;
		 }
	 }
	 while (!this->composition->isFulLeft()) this->composition->addMusicalSymbol(new Rest(Fraction::eight));
	 if (this->composition->getLeftHand().getTakts().empty()) throw new InputFileEmpty();
	 return true;
 }
std::string Piano::loadKeysMenu() {
	 std::cout << "Izabrali ste opciju podesavanje klavira!\n";
	 std::cout << "Unesite ime fajla u kome se nalazi klavir u formatu imefajla.csv!\n";
	 return  readFileName(".csv");
 }
 
 
		