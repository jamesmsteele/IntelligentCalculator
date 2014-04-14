#ifndef DECIMAL_H_
#define DECIMAL_H_

#include "expression.h"
#include "fraction.h"
#include "math.h"
#include <iostream>

class Decimal {

private:
	double value;
	double result;

public:
	//Constructors
	Decimal(double decimal);

	//Destructors
	~Decimal() {
	};

	//Methods
	void add(Expression addend);
	void subtract(Expression subtrahend);
	void divide(Expression dividend);
	void multiply(Expression multiplicand);
	void simplify();
	string toString();
	double getDecimal();
	double getResult();
	Fraction toFraction(double decimal);
	void toSimpleFrac();

};


#endif /* DECIMAL_H_ */
