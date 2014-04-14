#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include <vector>
#include <iostream>
#include "exception.h"

class Expression{
	private:
		Expression* value;
		bool initialized;
		std::vector<Expression*> addition;
		std::vector<Expression*> multiplication;
		void add_simplify();
		void multiply_simplify();

	public:
		Expression(Expression*);
		Expression(std::vector<Expression*>);
		Expression();
		~Expression();

		virtual void add(Expression*);
		virtual void subtract(Expression*);
		virtual void multiply(Expression*);
		virtual void divide(Expression*);
		virtual void exponentiate(Expression*);
		virtual void negative();
		virtual void simplify();
		virtual double toDecimal();
		virtual int getInt();

		virtual std::string toString();
		virtual std::string getName();
};

#endif // EXPRESSION_H_INCLUDED
