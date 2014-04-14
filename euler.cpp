#include "euler.h"

using namespace std;

Eulers::Eulers() {
	MathExInteger* co	=	new MathExInteger(1);
	this->coefficient.push_back(co);
}

string Eulers::getName() {
    return "Eulers";
}

string Eulers::toString() {
    return this->getCoefficient()->toString() + "e";
}

double Eulers::toDecimal() {
    return 2.7182818284 * this->getCoefficient()->toDecimal();
}

Expression* Eulers::getCoefficient() {
    return this->coefficient.back();
}

void Eulers::add(Expression* a) {
    throw (Exceptions("Eulers cannot add that data type."));
}

void Eulers::subtract(Expression* s) {
    throw (Exceptions("Eulers cannot subtract that data type."));
}

void Eulers::multiply(Expression* m) {
    throw (Exceptions("Eulers cannot multiply that data type."));
}

void Eulers::divide(Expression* d) {
    throw (Exceptions("Eulers cannot divide that data type."));
}

void Eulers::add(Eulers* a) {
    try {
        this->getCoefficient()->add(a->getCoefficient());
    }
    catch (Exceptions e) {
        Expression* exp = new Expression(this->getCoefficient());
        exp->add(a->getCoefficient());
        this->coefficient.push_back(exp);
    }
}

void Eulers::subtract(Eulers* s) {
    try {
        this->getCoefficient()->subtract(s->getCoefficient());
    }
    catch (Exceptions e) {
        Expression* exp = new Expression(this->getCoefficient());
        exp->subtract(s->getCoefficient());
        this->coefficient.push_back(exp);
    }
}

void Eulers::multiply(Eulers* m) {
    try {
        this->getCoefficient()->multiply(m->getCoefficient());
    }
    catch (Exceptions e) {
        Expression* exp = new Expression(this->getCoefficient());
        exp->multiply(m->getCoefficient());
        this->coefficient.push_back(exp);
    }
}

void Eulers::divide(Eulers* d) {
    try {
        this->getCoefficient()->divide(d->getCoefficient());
    }
    catch (Exceptions e) {
        Expression* exp = new Expression(this->getCoefficient());
        exp->divide(d->getCoefficient());
        this->coefficient.push_back(exp);
    }
}

void Eulers::negative() {
    MathExInteger* neg = new MathExInteger(-1);
    this->getCoefficient()->multiply(neg);
}
