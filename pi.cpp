#include "pi.h"

using namespace std;

Pi::Pi() {
	MathExInteger* co	=	new MathExInteger(1);
	this->coefficient.push_back(co);
}

string Pi::getName() {
    return "Pi";
}

string Pi::toString() {
    return this->getCoefficient()->toString() + "pi";
}

double Pi::toDecimal() {
    return 3.1415926535 * this->getCoefficient()->toDecimal();
}

Expression* Pi::getCoefficient() {
    return this->coefficient.back();
}

void Pi::add(Expression* a) {
    throw Exceptions("Cannot add constants with expressions");
}

void Pi::subtract(Expression* s) {
    throw Exceptions("Cannot subtract expressions from constants");
}

void Pi::multiply(Expression* m) {
    throw Exceptions("Cannot multiply constants by expressions");
}

void Pi::divide(Expression* d) {
    throw Exceptions("Cannot divide constants by expressions");
}

void Pi::add(Pi* a) {
    try {
        this->getCoefficient()->add(a->getCoefficient());
    }
    catch (Exceptions e) {
        Expression* exp = new Expression(this->getCoefficient());
        exp->add(a->getCoefficient());
        this->coefficient.push_back(exp);
    }
}

void Pi::subtract(Pi* s) {
    try {
        this->getCoefficient()->subtract(s->getCoefficient());
    }
    catch (Exceptions e) {
        Expression* exp = new Expression(this->getCoefficient());
        exp->subtract(s->getCoefficient());
        this->coefficient.push_back(exp);
    }
}

void Pi::multiply(Pi* m) {
    throw Exceptions("Cannot multiply constants");
}

void Pi::divide(Pi* d) {
    throw Exceptions("Cannot divide constants");
}

void Pi::negative() {
    MathExInteger* neg = new MathExInteger(-1);
    this->getCoefficient()->multiply(neg);
}
