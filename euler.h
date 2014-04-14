#ifndef EULERS_H_INCLUDED
#define EULERS_H_INCLUDED

#include "constant.h"
#include "exception.h"
#include "exp-integer.h"
#include <iostream>
#include <vector>


class Eulers : public Constant {
private:
    std::vector<Expression*> coefficient;

public:
    Eulers();

    void add(Expression* a);
    void subtract(Expression* s);
    void multiply(Expression* m);
    void divide(Expression* d);
    void add(Eulers* a);
    void subtract(Eulers* s);
    void multiply(Eulers* m);
    void divide(Eulers* d);

    void negative();
    Expression* getCoefficient();

    std::string getName();
    std::string toString();
    double toDecimal();
};

#endif // EULERS_H_INCLUDED
