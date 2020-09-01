#include "Fraction.h"

Fraction Fraction::one(1, 1);
Fraction Fraction::zero;
Fraction Fraction::quarter(4,1);
Fraction Fraction::eight(8,1);

int Fraction::greathestCommonDivider(int a, int b) {
	return 1;
}
Fraction Fraction::cutFraction() {
	int gcd = greathestCommonDivider(this->numerator, this->denominator);
	this->denominator /= gcd;
	this->numerator /= gcd;
	return *this;
}
