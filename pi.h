#ifndef PI_H_INCLUDED
#define PI_H_INCLUDED

#include "constant.h"
#include "exception.h"
#include "exp-integer.h"
#include <iostream>
#include <vector>

class Pi : public Constant {
private:
	std::vector<Expression*> coefficient;
public:
    Pi();
    ~Pi();

    void add(Pi* a);
    void add(Expression* a);
    void subtract(Pi* s);
    void subtract(Expression* s);
    void multiply(Expression* m);
    void multiply(Expression* m);
    void divide(Pi* d);
    void multiply(Pi* m);
    void negative();

    std::string getName();
    std::string toString();
    double toDecimal();
    Expression* getCoefficient();
};


#endif // PI_H_INCLUDED
