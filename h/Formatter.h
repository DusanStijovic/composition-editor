#ifndef _FORMATTER_H
#define _FORMATTER_H
#include "Composition.h"

class Formatter{
protected: 
	Composition* composition = nullptr;
public:
	virtual bool exportCompososition(std::string) = 0;
	Formatter(Composition* compo) :composition(compo) {}
	Formatter() {};
};
#endif // !_FORMATTER_H
