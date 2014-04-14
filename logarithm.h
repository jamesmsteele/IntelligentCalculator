#ifndef LOGARITHM_H_INCLUDED
#define LOGARITHM_H_INCLUDED

#include "expression.h"
#include "exponent.h"
#include "exp-integer.h"
#include "exception.h"
#include <iostream>
#include <vector>

class Exponent;

class Logarithm : public Expression{
	private:
		std::vector<Expression*> coefficient;
		std::vector<Expression*> base;
		std::vector<Expression*> argument;

	public:
		Logarithm(Expression*, Expression*, Expression*);
		Logarithm(Expression*, Expression*, Exponent*); // Check if base == Exponent.base, throws error: Simple logarithm
		Logarithm(Expression*, MathExInteger*, MathExInteger*); // If evaluates to a clean number, throws error: Simple expression
		~Logarithm();

		void add(Expression*); // Throws error: Cannot add expression to logarithm
		void subtract(Expression*); // Throws error: Cannot subtract expression from logarithm
		void multiply(Expression*); // Throws error: Cannot multiply expression with logarithm
		void multiply(Logarithm*); // Throws error: Cannot multiply logarithms
		void divide(Expression*); // Throws error: Cannot divide logarithm by expression

		void add(Logarithm*);
		void subtract(Logarithm*);
		void divide(Logarithm*);

		void negative();
		void simplify();
		std::string toString();
		double toDecimal();

		Expression* getCoefficient();
		Expression* getBase();
		Expression* getArgument();
		std::string getName();
};

#endif // LOGARITHM_H_INCLUDED
