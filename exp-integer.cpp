#include "exp-integer.h"
#include "expression.h"
#include <sstream>
#include <cmath>

using namespace std;

MathExInteger::MathExInteger() {
    me_int = 0;
}

MathExInteger::MathExInteger(int me_int) { //: me_int(me_int) {
	this->me_int = me_int;
}

void MathExInteger::add(MathExInteger* addend) {
    int result = me_int + addend->getInt();
    me_int = result;
}

void MathExInteger::subtract(MathExInteger* subtrahend){
    int result = me_int - subtrahend->getInt();
    me_int = result;
}

void MathExInteger::multiply(MathExInteger* multiplicand) {
    int result = me_int * multiplicand->getInt();
    me_int = result;
}

void MathExInteger::add(Expression* addend){
    throw Exceptions("Adding integer for non integer, will provide implementation for fractions once they exist");
}

void MathExInteger::subtract(Expression* s) {
    throw Exceptions("Subbing integer for non integer, will provide implementation for fractions once they exist");
}

void MathExInteger::divide(Expression* dividend) {
    throw Exceptions("Dividing integer for non integer, will provide implementation for fractions once they exist");
}

void MathExInteger::multiply(Expression* multiplicand) {
    throw Exceptions("Dividing integer for non integer, will provide implementation for fractions once they exist");
}

void MathExInteger::negative() {
    this->me_int	*=	-1;
}

void MathExInteger::simplify() {
    //DO NOTHING
}

int MathExInteger::getInt() {
    return me_int;
}

string MathExInteger::toString(){
	stringstream ss;
	ss << getInt();
	return ss.str();
}

string MathExInteger::getName() {
    return "Integer";
}

double MathExInteger::toDecimal() {
    return getInt();
}
