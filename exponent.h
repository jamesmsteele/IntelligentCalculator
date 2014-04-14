#ifndef EXPONENT_H_
#define EXPONENT_H_

#include <cmath>
#include <vector>
#include <iostream>

#include "expression.h"
#include "exp-integer.h"
#include "logarithm.h"
#include "fraction.h"

class Logarithm;
class Fraction;

class Exponent: public Expression{

private:
	std::vector<Expression*> base;
	std::vector<Expression*> power;
	std::vector<Expression*> coefficient;

public:
	Exponent(Expression*, Expression*, Expression*);
	Exponent(Expression*, Expression*, Logarithm*);
	Exponent(Expression*, Expression*, Fraction*);
	Exponent(Expression*, MathExInteger*, MathExInteger*);
	~Exponent();

	Expression* getCoefficient();
	Expression* getBase();
	Expression* getPower();

	void add(Expression* addend);
	void subtract(Expression* subtrahend);
	void multiply(Expression* multiplicand);
	void divide(Expression* dividend);

	void add(Exponent* addend);
	void subtract(Exponent* subtrahend);
	void multiply(Exponent* multiplicand);
	void divide(Exponent* dividend);

	void negative();
	void simplify();

	double toDecimal();

	std::string toString();
	std::string getName();

};


#endif /*EXPONENT_H_*/
