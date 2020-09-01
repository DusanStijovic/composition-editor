#include "Rest.h"

Rest* Rest::makeCopy()const {
	return new Rest(*this);
}
std::string Rest::type()const {
	return "REST";
}
std::string Rest::toString()const {
	return getDuration() == Fraction::eight ? "(1/8)" : "(1/4)";
}
Rest* Rest::getRest(MusicalSymbol* mS) {
	if (mS->type() == "REST")
		return dynamic_cast<Rest*>(mS);
	else
		return nullptr;
}
