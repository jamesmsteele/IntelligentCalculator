#include "logarithm.h"
#include <cmath>
#include <vector>

Logarithm::Logarithm(Expression* coefficient, Expression* base, Expression* argument){
	if(argument->toDecimal() == 0){
		throw Exceptions("Cannot have the logarithm of 0");
	}
	if(argument->toDecimal() == 1){
		throw Exceptions("Logarithm is equal to 0");
	}
	if(coefficient->toDecimal() == 0){
		throw Exceptions("Logarithm is equal to 0");
	}
	if(base->toDecimal() <= 0){
		throw Exceptions("Cannot have the logarithm of a negative number");
	}
	if(argument->toDecimal() <= 0){
		throw Exceptions("Cannot have the logarithm of a negative number");
	}
	if(log10(argument->toDecimal())/log10(base->toDecimal()) == floor(log10(argument->toDecimal())/log10(base->toDecimal()))){
		throw Exceptions("Evaluable Logarithm");
	}
	this->coefficient.push_back(coefficient);
	this->base.push_back(base);
	this->argument.push_back(argument);
}

Logarithm::Logarithm(Expression* coefficient, Expression* base, Exponent* argument){
	if(base->toDecimal() == argument->getBase()->toDecimal()){
		throw Exceptions("Simple Logarithm");
	}
	if(argument->toDecimal() == 0){
		throw Exceptions("Cannot have the logarithm of 0");
	}
	if(argument->toDecimal() == 1){
		throw Exceptions("Logarithm is equal to 0");
	}
	if(coefficient->toDecimal() == 0){
		throw Exceptions("Logarithm is equal to 0");
	}
	if(base->toDecimal() <= 0){
		throw Exceptions("Cannot have the logarithm of a negative number");
	}
	if(argument->toDecimal() <= 0){
		throw Exceptions("Cannot have the logarithm of a negative number");
	}
	if(log10(argument->toDecimal())/log10(base->toDecimal()) == floor(log10(argument->toDecimal())/log10(base->toDecimal()))){
		throw Exceptions("Evaluable Logarithm");
	}
	try{
		coefficient->multiply(argument->getPower());
		this->coefficient.push_back(coefficient);
	}catch(Exceptions e){
		Expression* exp	=	new Expression(coefficient);
		exp->multiply(argument->getPower());
		this->coefficient.push_back(exp);
	}
	this->base.push_back(base);
	this->argument.push_back(argument->getBase());
}

Logarithm::Logarithm(Expression* coefficient, MathExInteger* base, MathExInteger* argument){
	if(argument->toDecimal() == 0){
		throw Exceptions("Cannot have the logarithm of 0");
	}
	if(argument->toDecimal() == 1){
		throw Exceptions("Logarithm is equal to 0");
	}
	if(coefficient->toDecimal() == 0){
		throw Exceptions("Logarithm is equal to 0");
	}
	if(base->toDecimal() <= 0){
		throw Exceptions("Cannot have the logarithm of a negative number");
	}
	if(argument->toDecimal() <= 0){
		throw Exceptions("Cannot have the logarithm of a negative number");
	}
	if(log10(argument->toDecimal())/log10(base->toDecimal()) == floor(log10(argument->toDecimal())/log10(base->toDecimal()))){
		throw Exceptions("Evaluable Logarithm");
	}
	this->coefficient.push_back(coefficient);
	this->base.push_back(base);
	this->argument.push_back(argument);
}

/*
	These 5 methods will throw errors because of various logarithm rules
*/
void Logarithm::add(Expression* addend){
	throw Exceptions("Cannot add logarithms to that data type");
}
void Logarithm::subtract(Expression* addend){
	throw Exceptions("Cannot subtract a logarithm from that data type");
}
void Logarithm::multiply(Expression* addend){
	throw Exceptions("Cannot multiply a logarithm by that data type");
}
void Logarithm::multiply(Logarithm* addend){
	throw Exceptions("Cannot multiply logarithms");
}
void Logarithm::divide(Expression* addend){
	throw Exceptions("Cannot divide a logarithm by that data type");
}

void Logarithm::add(Logarithm* addend){
	bool samebase	=	addend->getBase()->toDecimal() == this->getBase()->toDecimal();
	bool samearg	=	addend->getArgument()->toDecimal() == this->getArgument()->toDecimal();
	if(samebase && samearg){
		try{
			this->getCoefficient()->add(addend->getCoefficient());
		}catch(Exceptions e){
			Expression* exp	=	new Expression(this->getCoefficient());
			exp->add(addend->getCoefficient());
			this->coefficient.push_back(exp);
		}
	}
	if(samebase && !samearg){
		try{
			this->getArgument()->multiply(addend->getArgument());
		}catch(Exceptions e){
			Expression* exp	=	new Expression(this->getCoefficient());
			exp->multiply(addend->getCoefficient());
			this->coefficient.push_back(exp);
		}
		try{
			this->getCoefficient()->add(addend->getCoefficient());
		}catch(Exceptions e){
			Expression* exp2	=	new Expression(this->getCoefficient());
			exp2->add(addend->getCoefficient());
			this->coefficient.push_back(exp2);
		}
	}
	if(!samebase && !samearg){
		throw "Cannot add logarithms with different bases";
	}
}

void Logarithm::subtract(Logarithm* subtrahend){
	bool samebase	=	subtrahend->getBase()->toDecimal() == this->getBase()->toDecimal();
	bool samearg	=	subtrahend->getArgument()->toDecimal() == this->getArgument()->toDecimal();
	if(samebase && samearg){
		try{
			this->getCoefficient()->subtract(subtrahend->getCoefficient());
		}catch(Exceptions e){
			Expression* exp	=	new Expression(this->getCoefficient());
			exp->subtract(subtrahend->getCoefficient());
			this->coefficient.push_back(exp);
		}
	}
	if(samebase && !samearg){
		try{
			this->getArgument()->divide(subtrahend->getArgument());
		}catch(Exceptions e){
			Expression* exp	=	new Expression(this->getCoefficient());
			exp->divide(subtrahend->getCoefficient());
			this->coefficient.push_back(exp);
		}
		try{
			this->getCoefficient()->subtract(subtrahend->getCoefficient());
		}catch(Exceptions e){
			Expression* exp2	=	new Expression(this->getCoefficient());
			exp2->subtract(subtrahend->getCoefficient());
			this->coefficient.push_back(exp2);
		}
	}
	if(!samebase && !samearg){
		throw "Cannot subtract logarithms with different bases";
	}
}

void Logarithm::divide(Logarithm* dividend){
	this->base.push_back(dividend->getArgument());
}

void Logarithm::negative(){
	this->getCoefficient()->negative();
}
void Logarithm::simplify(){
	// Do nothing
}

std::string Logarithm::toString(){
	std::string result	=	"";
	if(this->getCoefficient()->toDecimal() != 1){
		result	+=	this->getCoefficient()->toString();
	}
	result	+=	"log_";
	result	+=	this->getBase()->toString();
	result	+=	":(";
	result	+=	this->getArgument()->toString();
	result	+=	")";
	return result;
}

double Logarithm::toDecimal(){
	double log	=	log10(this->getArgument()->toDecimal())/log10(this->getBase()->toDecimal());
	log *=	this->getCoefficient()->toDecimal();
	return log;
}

Expression* Logarithm::getCoefficient(){
	return this->coefficient.back();
}
Expression* Logarithm::getBase(){
	return this->base.back();
}
Expression* Logarithm::getArgument(){
	return this->argument.back();
}
std::string Logarithm::getName(){
	return "Logarithm";
}

Logarithm::~Logarithm(){
	this->base.clear();
	this->coefficient.clear();
	this->argument.clear();
}
