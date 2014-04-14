#include "fraction.h"
#include "exp-integer.h"
#include "expression.h"
#include <math.h>
#include <stdio.h>

Fraction::Fraction() {
    MathExInteger* numer	=	new MathExInteger(1);
    MathExInteger* denom	=	new MathExInteger(1);
    this->numerator.push_back(numer);
    this->denominator.push_back(denom);
}

Fraction::Fraction(Expression* numerator, Expression* denominator){
    if (denominator->toDecimal() == 0){
        throw Exceptions("Cannot divide by zero");
    }
    numerator->simplify();
    denominator->simplify();

    this->numerator.push_back(numerator);
    this->denominator.push_back(denominator);
    this->simplify();
}

Expression* Fraction::getNumerator() {
    return this->numerator.back();
}

Expression* Fraction::getDenominator() {
    return this->denominator.back();
}

int Fraction::GCDivisor(int x,int y){
	if(y!=0){
		this->GCDivisor(y,x%y); //recursive call by using arithmetic rules
	}else{
		return x; //base case,return x when y equals 0
	}
}

int Fraction::GCDivisor(){
	if(this->getNumerator()->getName() == "Integer" && this->getDenominator()->getName() == "Integer") {
        return this->GCDivisor(this->getNumerator()->getInt(), this->getDenominator()->getInt());
    }else{
    	throw Exceptions("Trying to get GCD of non-integer");
	}
}

void Fraction::simplify(){
    if(this->getNumerator()->getName() == "Integer" && this->getDenominator()->getName() == "Integer"){
        int gcd = this->GCDivisor();

        int num	=	this->getNumerator()->getInt();
        int den	=	this->getDenominator()->getInt();

        MathExInteger* n	=	new MathExInteger(num/gcd);
        MathExInteger* d	=	new MathExInteger(den/gcd);

        this->numerator.push_back(n);
        this->denominator.push_back(d);

        if(this->getDenominator()->getInt() == 1){
            throw Exceptions("Denominator is equal to 1, don't need fraction");
        }
    }else if(this->toDecimal() - floor(this->toDecimal()) < 0.000001){
        throw Exceptions("Denominator is equal to 1, don't need fraction");
    }else if(ceil(this->toDecimal()) - this->toDecimal() < 0.000001){
        throw Exceptions("Denominator is equal to 1, don't need fraction");
    }
}

double Fraction::toDecimal(){
    double decimal = this->getNumerator()->toDecimal() / this->getDenominator()->toDecimal();
    return decimal;
}

std::string Fraction::toString(){
    std::string str = this->getNumerator()->toString() + "/" + this->getDenominator()->toString();
    return str;
}

std::string Fraction::getName() {
    return "Fraction";
}

void Fraction::add(Expression* addend){
    throw Exceptions("Fraction cannot add that type.");
}

void Fraction::add(Fraction* addend){
    addend->simplify();
    try{
    	try{
        	this->getNumerator()->multiply(addend->getDenominator());
    	}catch(Exceptions e){
    		throw Exceptions("Operation failed");
    	}

    	try{
        	this->getDenominator()->multiply(addend->getDenominator());
    	}catch(Exceptions e){
        	this->numerator.pop_back();
    		throw Exceptions("Operation failed");
    	}

    	try{
        	addend->getNumerator()->multiply(this->getDenominator());
    	}catch(Exceptions e){
        	this->numerator.pop_back();
        	this->denominator.pop_back();
    		throw Exceptions("Operation failed");
    	}

    	try{
        	this->getNumerator()->add(addend->getNumerator());
    	}catch(Exceptions e){
        	this->numerator.pop_back();
        	this->numerator.pop_back();
        	this->denominator.pop_back();
    		throw Exceptions("Operation failed");
    	}
        this->simplify();
    }catch(Exceptions e) {
        Expression* expp = new Expression(this->getNumerator());
        expp->multiply(addend->getDenominator());

        Expression* expp2 = new Expression(addend->getNumerator());
        expp2->multiply(this->getDenominator());

        Expression* exppd = new Expression(this->getDenominator());

        exppd->multiply(addend->getDenominator());
        expp->add(expp2);

        this->numerator.push_back(expp);
        this->denominator.push_back(exppd);
        delete expp2;
    }
}

void Fraction::subtract(Fraction* subtrahend){
    subtrahend->simplify();
    try{
    	try{
        	this->getNumerator()->multiply(subtrahend->getDenominator());
    	}catch(Exceptions e){
    		throw Exceptions("Operation failed");
    	}

    	try{
        	this->getDenominator()->multiply(subtrahend->getDenominator());
    	}catch(Exceptions e){
        	this->numerator.pop_back();
    		throw Exceptions("Operation failed");
    	}

    	try{
        	subtrahend->getNumerator()->multiply(this->getDenominator());
    	}catch(Exceptions e){
        	this->numerator.pop_back();
        	this->denominator.pop_back();
    		throw Exceptions("Operation failed");
    	}

    	try{
        	this->getNumerator()->subtract(subtrahend->getNumerator());
    	}catch(Exceptions e){
        	this->numerator.pop_back();
        	this->numerator.pop_back();
        	this->denominator.pop_back();
    		throw Exceptions("Operation failed");
    	}
        this->simplify();
    }catch(Exceptions e) {
        Expression* expp = new Expression(this->getNumerator());
        expp->multiply(subtrahend->getDenominator());

        Expression* expp2 = new Expression(subtrahend->getNumerator());
        expp2->multiply(this->getDenominator());

        Expression* exppd = new Expression(this->getDenominator());

        exppd->multiply(subtrahend->getDenominator());
        expp->subtract(expp2);

        this->numerator.push_back(expp);
        this->denominator.push_back(exppd);
        delete expp2;
    }
}

void Fraction::multiply(Fraction* multiplicand){
    multiplicand->simplify();
    try {
    	try{
    		this->getNumerator()->multiply(multiplicand->getNumerator());
    	}catch(Exceptions e){
    		throw("Operation failed");
    	}

    	try{
        this->getDenominator()->multiply(multiplicand->getDenominator());
    	}catch(Exceptions e){
    		this->numerator.pop_back();
    		throw("Operation failed");
    	}
        this->simplify();
    } catch (Exceptions e) {
        Expression* exppn = new Expression(this->getNumerator());
        exppn->multiply(multiplicand->getNumerator());

        Expression* exppd = new Expression(this->getDenominator());
        exppd->multiply(multiplicand->getDenominator());

        this->numerator.push_back(exppn);
        this->denominator.push_back(exppd);
    }
}

void Fraction::divide(Fraction* dividend){
    dividend->simplify();
    try {
    	try{
    		this->getNumerator()->multiply(dividend->getDenominator());
    	}catch(Exceptions e){
    		throw("Operation failed");
    	}

    	try{
        this->getDenominator()->multiply(dividend->getNumerator());
    	}catch(Exceptions e){
    		this->numerator.pop_back();
    		throw("Operation failed");
    	}
        this->simplify();
    } catch (Exceptions e) {
        Expression* exppn = new Expression(this->getNumerator());
        exppn->multiply(dividend->getDenominator());

        Expression* exppd = new Expression(this->getDenominator());
        exppd->multiply(dividend->getNumerator());

        this->numerator.push_back(exppn);
        this->denominator.push_back(exppd);
    }
}

void Fraction::subtract(Expression* value){
	throw Exceptions("Cannot subtract from fraction");
}
void Fraction::divide(Expression* value){
	throw Exceptions("Cannot divide by fraction");
}
void Fraction::multiply(Expression* value){
	throw Exceptions("Cannot multiply by fraction");
}
