#include "exception.h"
#include <vector>
#include <iostream>

Exceptions::Exceptions() {
	this->errorName = "invalid";
	this->errorID = 0;
}

Exceptions::Exceptions(string name) {
	this->errorName = name;
	determineError(errorName);
}

void Exceptions::determineError(string errorName) {
	//Fractional errors
	if(errorName.compare("Cannot divide by zero") == 0){
		errorID = 1;
	}else if (errorName.compare("Trying to get GCD of non-integer") == 0) {
		errorID = 2;
	} else if (errorName.compare("Denominator is equal to 1, don't need fraction") == 0) {
		errorID = 3;
	} else if (errorName.compare("Cannot have the logarithm of a negative number") == 0) {
		errorID = 4;
	} else if (errorName.compare("Cannot have the logarithm of 0") == 0) {
		errorID = 5;
	} else if (errorName.compare("Logarithm is equal to 0") == 0) {
		errorID = 6;
	} else if (errorName.compare("Cannot add logarithms to that data type") == 0) {
		errorID = 7;
	} else if (errorName.compare("Cannot subtract a logarithm from that data type") == 0) {
		errorID = 8;
	} else if (errorName.compare("Cannot divide a logarithm by that data type") == 0) {
		errorID = 9;
	} else if (errorName.compare("Cannot multiply a logarithm by that data type") == 0) {
		errorID = 10;
	} else if (errorName.compare("Simple Logarithm") == 0) {
		errorID = 11;
	} else if (errorName.compare("Evaluable Logarithm") == 0) {
		errorID = 12;
	} else if (errorName.compare("Cannot multiply logarithms") == 0) {
		errorID = 13;
	}else if (errorName.compare("Integer Class: Adding non-integer") == 0) {
		errorID = 14;
	} else if (errorName.compare("Integer Class: Subtracting non-integer") == 0) {
		errorID = 15;
	} else if (errorName.compare("Integer Class: Dividing non-integer")) {
		errorID = 16;
	} else if (errorName.compare("Integer Class: Multiplying non-integer") == 0) {
		errorID = 17;
	} else if (errorName.compare("Create the reciprocal") == 0) {
		errorID = 18;
	} else if (errorName.compare("Use exponent class instead") == 0) {
		errorID = 19;
	} else if (errorName.compare("Exponent Class: power < 0, convert to fraction") == 0) {
		errorID = 20;
	} else if (errorName.compare("Exponent Class: power = 0, convert to 1") == 0) {
		errorID = 21;
	} else if (errorName.compare("Exponent Class: power == 1, convert to integer") == 0) {
		errorID = 22;
	} else if (errorName.compare("Exponent Class: base == 0, convert to 0") == 0) {
		errorID = 23;
	} else if (errorName.compare("Exponent Class: base == 1, convert to 1") == 0) {
		errorID = 21;
	} else if (errorName.compare("Exponent Class: Entire expression is undefined") == 0) {
		errorID = 24;
	} else if (errorName.compare("Exponent Class: evaluable exponent with expression base and logarithm power") == 0) {
		errorID = 25;
	} else if (errorName.compare("Exponent Class: evaluable exponent with MathExInteger base and MathExInteger power") == 0) {
		errorID = 26;
	} else if (errorName.compare("Exponent::add(Expression*) : add math expression to exponent") == 0) {
        errorID = 27;
	} else if (errorName.compare("Exponent::subtract(Expression*) : subtract math expression from exponent") == 0) {
        errorID = 28;
    } else if (errorName.compare("Exponent::multiply(Expression*) : multiply math expression to exponent") == 0) {
        errorID = 29;
    } else if (errorName.compare("Exponent::divide(Expression*) : divide math expression from exponent") == 0) {
        errorID = 30;
    } else {
		errorID = 0;
	}

	//Other errors
}

int Exceptions::what() {
	return errorID;
}

string Exceptions::whatString(){
	return this->errorName;
}
