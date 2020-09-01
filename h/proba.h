#pragma once
/*void MakeNewIfHandsFull() {
		if (currentRight->isFull()) {
			currentRight->setTaktID(IDRight++);
			rightHand.addTakt(currentRight);
			currentRight = new Takt(takt);
		}
		if (currentLetf->isFull()) {
			currentLetf->setTaktID(IDLeft++);
			leftHand.addTakt(currentLetf);
			currentLetf = new Takt(takt);
		}
	}
	bool addMusicalSymbolLeft(MusicalSymbol* symbol, Pause pause) {
		if (!currentLetf->addSymbol(symbol)) {
			if (symbol->getDuration() == Fraction::eight) throw BadInputFile(2);
			MusicalSymbol* symbol1 = symbol->makeCopy();
			symbol1->setSymbolAsFirstPair();
			symbol1->setDuration(Fraction::eight);
			MusicalSymbol* symbol2 = symbol->makeCopy();
			symbol2->setSymbolAsPair();
			symbol2->setDuration(Fraction::eight);
			if (!currentLetf->addSymbol(symbol1)) throw BadInputFile(3);
			currentLetf->setTaktID(IDLeft++);
			leftHand.addTakt(currentLetf);
			currentLetf = new Takt(takt);
			currentLetf->addSymbol(symbol2);
			if (pause == YES) {
				currentRight->addSymbol(new Rest(Fraction::eight));
				currentRight->setTaktID(IDRight++);
				rightHand.addTakt(currentRight);
				currentRight = new Takt(takt);
				currentRight->addSymbol(new Rest(Fraction::eight));
			}
		}
		else {
			if (pause == YES) {
				currentRight->addSymbol(new Rest(symbol->getDuration()));
			}
			MakeNewIfHandsFull();
		}

		return true;
	};
	bool addMusicalSymbolRight(MusicalSymbol* symbol, Pause pause) {
		if (!currentRight->addSymbol(symbol)) {
			if (symbol->getDuration() == Fraction::eight) throw BadInputFile(2);
			MusicalSymbol* symbol1 = symbol->makeCopy();
			symbol1->setSymbolAsFirstPair();
			MusicalSymbol* symbol2 = symbol->makeCopy();
			symbol2->setSymbolAsPair();
			if (!currentRight->addSymbol(symbol1))  throw BadInputFile(2);
			currentRight->setTaktID(IDRight++);
			rightHand.addTakt(currentRight);
			currentRight = new Takt(takt);
			currentRight->addSymbol(symbol2);
			if (pause == YES) {
				currentLetf->addSymbol(new Rest(Fraction::eight));
				currentLetf->setTaktID(IDLeft++);
				leftHand.addTakt(currentLetf);
				currentLetf = new Takt(takt);
				currentLetf->addSymbol(new Rest(Fraction::eight));
			}
		}
		else {
			if (pause == YES) {
				currentLetf->addSymbol(new Rest(symbol->getDuration()));
			}
			MakeNewIfHandsFull();
		}

		return true;
	};
	*/
/*

void Composition::iterateComposition() {
	auto currentL = leftHand.getTakts().begin();
	auto currentR = rightHand.getTakts().begin();
	auto beginningL = leftHand.getTakts().begin();
	auto beginningR = rightHand.getTakts().begin();
	auto endL = leftHand.getTakts().end();
	endL--;
	auto endR = rightHand.getTakts().end();
	endR--;
	bool finished = false;
	std::cout << "Izabrali ste iteriranje kroz taktove kompozicije!\n";

	while (!finished) {
		std::cout << "Nalazite se na taktu:" << (*currentL)->getTaktID() << std::endl;
		std::cout << "Takt izgleda ovako:\n";
		std::pair<std::string, std::string> description = Takt::toString(**currentL, **currentR);
		std::cout << description.first << std::endl << description.second << std::endl;
		Choice choice = this->choice();
		std::cout << std::setfill('_') << std::setw(40) << "\n";
		switch (choice) {
		case Choice::TAKTBACK:
			if (currentL == beginningL or currentR == beginningR) {//dovoljno je jedan uslov, posto imamo isto taktova u obe ruke.
				std::cout << "Nalazite se na prvom taktu, ne mozete preci na prethodni takt!\n";
				break;
			}
			currentL--;
			currentR--;
			break;
		case Choice::TAKTFOWARD:
			if (currentL == endL or currentR == endR) {//dovoljno je jedan uslov, posto imamo isto taktova u obe ruke.
				std::cout << "Nalazite se na poslednjem taktu taktu, ne mozete preci na sledeci takt!\n";
				break;
			}
			currentL++;
			currentR++;
			break;
		case Choice::GOINTAKT:
			if (choice == Choice::GOINTAKT) {
				Takt::iterateTakt(*currentL, *currentR);
			}
			break;
		case Choice::BACKTOMAINMANU:
			return;
		}
	}
}
*/