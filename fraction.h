#ifndef __calculator__Fraction__
#define __calculator__Fraction__

#include <iostream>
#include <vector>
#include "expression.h"


class Fraction : public Expression{
private:
    std::vector<Expression*> numerator;
    std::vector<Expression*> denominator;

public:
    Fraction(Expression* numerator, Expression* denominator);
    Fraction();

    void add(Expression* addend);
    void add(Fraction* addend);

    void subtract(Expression* subtrahend);
    void subtract(Fraction* subtrahend);

    void divide(Expression* dividend);
    void divide(Fraction* dividend);

    void multiply(Expression* multiplicand);
    void multiply(Fraction* multiplicand);

    void simplify();
    int GCDivisor();
    int GCDivisor(int, int);

    Expression* getNumerator();
    Expression* getDenominator();

    std::string toString();
    double toDecimal();
    std::string getName();

};


#endif /* defined(__calculator__Fraction__) */
