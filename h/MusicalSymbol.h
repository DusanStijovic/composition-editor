 #ifndef _MUSICALSYMBOL_H
#define _MUSICALSYMBOL_H
#include "Fraction.h"
#include <string>
#include<list>
#include <map>
#include <vector>
#define and &&
#define or ||
class Note;
class Chord;
class MusicalSymbol {
private:
	Fraction duration;
	bool partOfSymbol = false;
protected:
	bool firstPart = false;
public:
	enum class Color { R, G, B };
	MusicalSymbol(Fraction duration);
	Fraction getDuration()const { return duration; }
	virtual ~MusicalSymbol() {};
	virtual MusicalSymbol* makeCopy() const = 0;
	virtual void setDuration(Fraction duration);
	virtual void setSymbolAsFirstPair();
	virtual void setSymbolAsPair();
	bool isPartOfSymbol() const { return partOfSymbol; }
	bool isFirstpart() const { return firstPart; }
	virtual std::string toString() const = 0;
	virtual std::string type() const = 0;
	virtual void addSymbol(std::list<Note*>& notes) = 0;
	virtual bool connectSymbols(MusicalSymbol*) { return false; }
	virtual MusicalSymbol* newSymbol() const = 0;
};

#endif