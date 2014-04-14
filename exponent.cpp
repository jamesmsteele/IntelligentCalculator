#include "Exponent.h"
#include <stdio.h>

Exponent::Exponent(Expression* coefficient, Expression* base, Expression* power){
	if(power->toDecimal() < 0){
		throw Exceptions("Exponent Class: power < 0, convert to fraction");
	}

	if(power->toDecimal() == 0){
		throw Exceptions("Exponent Class: power = 0, convert to 1");
	}

	if(power->toDecimal() == 1){
		throw Exceptions("Exponent Class: power == 1, convert to integer");
	}

	if(base->toDecimal() == 0){
		throw Exceptions("Exponent Class: base == 0, convert to 0");
	}

	if(base->toDecimal() == 1){
		throw Exceptions("Exponent Class: base == 1, convert to 1");
	}

	if((base->toDecimal() == 0) && (power->toDecimal() == 0)){
		throw Exceptions("Exponent Class: Entire expression is undefined");
	}

	if(abs(pow(base->toDecimal(),power->toDecimal()) - floor(pow(base->toDecimal(),power->toDecimal()))) <= .001){
		throw Exceptions("Exponent Class: evaluable exponent with MathExInteger base and MathExInteger power");
	}

	this->coefficient.push_back(coefficient);
	this->base.push_back(base);
	this->power.push_back(power);

}

Exponent::Exponent(Expression* coefficient, Expression* base, Logarithm* power){
	if(power->toDecimal() < 0){
		throw Exceptions("Exponent Class: power < 0, convert to fraction");
	}

	if(power->toDecimal() == 0){
		throw Exceptions("Exponent Class: power = 0, convert to 1");
	}

	if(power->toDecimal() == 1){
		throw Exceptions("Exponent Class: power == 1, convert to integer");
	}

	if(base->toDecimal() == 0){
		throw Exceptions("Exponent Class: base == 0, convert to 0");
	}

	if(base->toDecimal() == 1){
		throw Exceptions("Exponent Class: base == 1, convert to 1");
	}

	if((base->toDecimal() == 0) && (power->toDecimal() == 0)){
		throw Exceptions("Exponent Class: Entire expression is undefined");
	}

	if (base->toDecimal() == power->getBase()->toDecimal()){
		throw Exceptions("Exponent Class: evaluable exponent with expression base and logarithm power");
	}

	if(abs(pow(base->toDecimal(),power->toDecimal()) - floor(pow(base->toDecimal(),power->toDecimal()))) <= .001){
		throw Exceptions("Exponent Class: evaluable exponent with MathExInteger base and MathExInteger power");
	}
}


Exponent::Exponent(Expression* coefficient, MathExInteger* base, MathExInteger* power){
	if(power->toDecimal() < 0){
		throw Exceptions("Exponent Class: power < 0, convert to fraction");
	}

	if(power->toDecimal() == 0){
		throw Exceptions("Exponent Class: power = 0, convert to 1");
	}

	if(power->toDecimal() == 1){
		throw Exceptions("Exponent Class: power == 1, convert to integer");
	}

	if(base->toDecimal() == 0){
		throw Exceptions("Exponent Class: base == 0, convert to 0");
	}

	if(base->toDecimal() == 1){
		throw Exceptions("Exponent Class: base == 1, convert to 1");
	}

	if((base->toDecimal() == 0) && (power->toDecimal() == 0)){
		throw Exceptions("Exponent Class: Entire expression is undefined");
	}

	if(abs(pow(base->toDecimal(),power->toDecimal()) - floor(pow(base->toDecimal(),power->toDecimal()))) <=.001){
		throw Exceptions("Exponent Class: evaluable exponent with MathExInteger base and MathExInteger power");
	}

	//Should not get to this point because the exponent should always be evaluable since base and power are of type MathExInteger
	this->coefficient.push_back(coefficient);
	this->base.push_back(base);
	this->power.push_back(power);
}

Exponent::Exponent(Expression* coefficient, Expression* base, Fraction* power){
	if(power->toDecimal() < 0){
		throw Exceptions("Exponent Class: power < 0, convert to fraction");
	}

	if(power->toDecimal() == 0){
		throw Exceptions("Exponent Class: power = 0, convert to 1");
	}

	if(power->toDecimal() == 1){
		throw Exceptions("Exponent Class: power == 1, convert to integer");
	}

	if(base->toDecimal() == 0){
		throw Exceptions("Exponent Class: base == 0, convert to 0");
	}

	if(base->toDecimal() == 1){
		throw Exceptions("Exponent Class: base == 1, convert to 1");
	}

	if((base->toDecimal() == 0) && (power->toDecimal() == 0)){
		throw Exceptions("Exponent Class: Entire expression is undefined");
	}

	if(abs(pow(base->toDecimal(), power->toDecimal()) - floor(pow(base->toDecimal(),power->toDecimal()))) <= .001){
		throw Exceptions("Exponent Class: evaluable exponent with MathExInteger base and MathExInteger power");
	}

	//Should not get to this point because the exponent should always be evaluable since base and power are of type MathExInteger
	this->coefficient.push_back(coefficient);
	this->base.push_back(base);
	this->power.push_back(power);
}


Exponent::~Exponent(){
	this->base.clear();
	this->coefficient.clear();
	this->power.clear();
}

Expression* Exponent::getCoefficient(){
	return this->coefficient.back();
}

Expression* Exponent::getBase(){
	return this->base.back();
}

Expression* Exponent::getPower(){
	return this->power.back();
}

void Exponent::add(Expression* addend){

	throw Exceptions("Exponent::add(Expression*) : add math expression to exponent");

}

void Exponent::subtract(Expression* subtrahend){
	if(this->toDecimal() == subtrahend->toDecimal()){
		throw Exceptions("Exponent::subtract(Expression*) : subtraction of same values, convert to 0");
	}
	else
	throw Exceptions("Exponent::subtract(Expression*) : subtract math expression from exponent");

}

void Exponent::multiply(Expression* multiplicand){

	throw Exceptions("Exponent::multiply(Expression*) : multiply math expression to exponent");

}

void Exponent::divide(Expression* dividend){

	throw Exceptions("Exponent::divide(Expression*) : divide math expression from exponent");

}

void Exponent::add(Exponent* addend){

bool sameBase = addend->getBase()->toDecimal() == this->getBase()->toDecimal();
bool samePow  = addend->getPower()->toDecimal() == this->getPower()->toDecimal();
	if(sameBase && samePow){
		try{
			this->getCoefficient()->add(addend->getCoefficient());
		}catch(Exceptions e){
			Expression* exp2	=	new Expression(this->getCoefficient());
			exp2->add(addend->getCoefficient());
			this->coefficient.push_back(exp2);
		}
	}
	else{
		throw Exceptions("Exponent::add(Exponent*) : add exponent to exponent");
	}
}

void Exponent::subtract(Exponent* subtrahend){

bool sameCoeff = subtrahend->getCoefficient()->toDecimal() == this->getCoefficient()->toDecimal();
bool sameBase = subtrahend->getBase()->toDecimal() == this->getBase()->toDecimal();
bool samePow  = subtrahend->getPower()->toDecimal() == this->getPower()->toDecimal();

	if(sameCoeff && sameBase && samePow){
		throw Exceptions("Exponent::subtract(Exponent*) : subtraction of same exponents, convert to 0");
	}
	if(sameBase && samePow){
		try{
			this->getCoefficient()->subtract(subtrahend->getCoefficient());
		}catch(Exceptions e){
			Expression* exp2	=	new Expression(this->getCoefficient());
			exp2->subtract(subtrahend->getCoefficient());
			this->coefficient.push_back(exp2);
		}
	}
	else{
		throw Exceptions("Exponent::subtract(Exponent*) : subtract exponent from exponent");
	}
}


void Exponent::multiply(Exponent* multiplicand){
	bool sameBase = multiplicand->getBase()->toDecimal() == this->getBase()->toDecimal();

	if(sameBase){
		try{
			this->getCoefficient()->multiply(multiplicand->getCoefficient());
			this->getPower()->add(multiplicand->getPower());
		}catch(Exceptions e){
			Expression* exp1	=	new Expression(this->getCoefficient());
			Expression* exp2	=	new Expression(this->getPower());
			exp1->multiply(multiplicand->getCoefficient());
			exp2->add(multiplicand->getPower());
			this->coefficient.push_back(exp1);
			this->power.push_back(exp2);
		}
	}
	else{
		throw Exceptions("Exponent::multiply(Exponent*) : multiply exponent to exponent");
	}

}

void Exponent::divide(Exponent* dividend){
	bool sameBase = dividend->getBase()->toDecimal() == this->getBase()->toDecimal();

	if(sameBase){
		try{
			this->getCoefficient()->divide(dividend->getCoefficient());
			this->getPower()->subtract(dividend->getPower());
		}catch(Exceptions e){
			Expression* exp1	=	new Expression(this->getCoefficient());
			Expression* exp2	=	new Expression(this->getPower());
			exp1->divide(dividend->getCoefficient());
			exp2->subtract(dividend->getPower());
			this->coefficient.push_back(exp1);
			this->power.push_back(exp2);
		}
	}
	else{
		throw Exceptions("Exponent::divide(Exponent*) : divide exponent by exponent");
	}

}

void Exponent::negative(){
	this->getCoefficient()->negative();

}

void Exponent::simplify(){
	//do nothing

}

double Exponent::toDecimal(){
	double exponentVal = pow(this->getBase()->toDecimal(),this->getPower()->toDecimal());
	exponentVal *= this->getCoefficient()->toDecimal();
	return exponentVal;

}

std::string Exponent::toString(){
	return this->getCoefficient()->toString() + "(" + this->getBase()->toString() + "^" + this->getPower()->toString() + ")";
}

std::string Exponent::getName(){
	return "Exponent";
}

