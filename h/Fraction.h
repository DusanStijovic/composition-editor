#ifndef _FRACTION_H
#define _FRACTION_H
#include <numeric>
class Fraction{
private:
	int numerator, denominator;
	static int greathestCommonDivider(int a, int b);
	Fraction cutFraction();
public:
	static Fraction zero;
	static Fraction one;
	static Fraction quarter;
	static Fraction eight;
	Fraction(int denominator = 1, int numerator = 0) {
		this->numerator = numerator;
		this->denominator = denominator;
	}
	int getNumerator() const { return numerator; }
	int getDenomitot() const { return denominator; }
	friend bool operator==(const Fraction& fraction1, const Fraction& fraction2) {
		return (fraction1.numerator * fraction2.denominator - fraction2.numerator * fraction1.denominator) == 0;
	}
	friend Fraction operator+(const Fraction& fraction1, const Fraction& fraction2) {
		Fraction sum;
		sum.denominator = fraction1.denominator * fraction2.denominator;
		sum.numerator = fraction1.numerator * fraction2.denominator + fraction2.numerator * fraction1.denominator;
		return sum;
	}
	friend bool operator>(const Fraction & fraction1, const Fraction & fraction2){
		return fraction1.numerator* fraction2.denominator - fraction2.numerator * fraction1.denominator > 0;
	}
	friend bool operator<(const Fraction& fraction1, const Fraction& fraction2) {
		return fraction1.numerator* fraction2.denominator - fraction2.numerator * fraction1.denominator < 0;
	}


};














#endif


