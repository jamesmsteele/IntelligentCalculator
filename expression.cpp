#include <vector>
#include "expression.h"

Expression::Expression(Expression* exp){
	/*
		If we only want to add one expression, we'll set value equal to the expression and set initialized to false.
		This will tell our other methods to move value to the first slot of the appropriate vector.
	*/
	this->value	=	exp;
	this->initialized	=	false;
}
Expression::Expression(){
	/*
		If we want to create an empty expression, we'll set initialized to true to indicate that value doesn't need
		to be placed in the first slot of a vector when add() or multiply() is called.
	*/
	this->initialized	=	true;
}
Expression::Expression(std::vector<Expression*> addition){
	/*
		In some cases, we'll want to accept an addition vector, which allows us to multiply. More information will be
		in our multiply() method.
	*/
	this->initialized	=	true;
	this->addition		=	addition;
}
void Expression::add(Expression* addend){
	/*
		If initialized is true, we don't need to worry about the value variable.
	*/
	if(this->initialized){
		this->addition.push_back(addend);
	}
	/*
		Otherwise, we need to set it to true, put it in our addition vector, then conduct business as usual.
	*/
	else{
		this->initialized	=	true;
		this->addition.push_back(value);
		this->addition.push_back(addend);
	}
}
void Expression::subtract(Expression* subtrahend){
	/*
		We call negative() on our subtrahend so that we can add it to our addition vector.
		This allows us to avoid having a vector just for subtraction, which makes our lives a lot easier.
	*/
	subtrahend->negative();
	this->add(subtrahend);
}
void Expression::multiply(Expression* multiplicand){
	/*
		Like in the addition method, we have to handle our value variable.
	*/
	if(!this->initialized){
		this->initialized	=	true;
		this->multiplication.push_back(value);
	}
	/*
		If our expression has an addition vector, we need to put it in our multiplication vector.
		For example, if we multiply "log_5:10 +  e^5" by "pi^6", we would take [log_5:10*, e^5*], turn it into
		an Expression object via the vector constructor, then we'd have a multiplication vector of [[log_5:10*, e^5*], pi^6].
	*/
	if(!this->addition.empty()){
		this->add_simplify();
		Expression* exp	=	new Expression(this->addition);
		this->addition.clear();
		this->multiplication.push_back(exp);
	}
	this->multiplication.push_back(multiplicand);
}
void Expression::divide(Expression* dividend){
	/*
		Tell the parser to multiply by the reciprocal instead of dividing.
	*/
	throw "Create the reciprocal";
}
void Expression::negative(){
	if(!this->multiplication.empty()){
		this->multiplication.back()->negative();
	}else{
		int c	=	this->addition.size();
		for(int i = 0; i < c; i++){
			this->addition[c]->negative();
		}
	}
}
void Expression::exponentiate(Expression* exponent){
	/*
		We don't need to handle exponents. It's easier to just do Exponent(Expression, exponent).
	*/
	throw "Use exponent class instead";
}
void Expression::add_simplify(){
	/*
		Ideally, we wouldn't go through this vector linearly,
		but it's unlikely that the size is very large, so it shouldn't be that bad.
	*/
	/*
		We seek through our vector and add anything together that can be added together.
		For example, [5, log_5:10, 10] would become [15, log_5:10].
	*/
	
	for(int i = 0; i < this->addition.size(); i++){
		for(int j = 0; j < this->addition.size(); j++){
			try{
				this->addition[i]->add(this->addition[j]);
				this->addition.erase(this->addition.begin()+j);
			}catch(Exceptions e){
				cout << e.whatString() << endl;
			}
		}
	}
}
void Expression::multiply_simplify(){
	/*
		Just like the add_simplify() method, except with multiplication.
	*/
	int c	=	this->multiplication.size();
	for(int i = 0; i < this->multiplication.size(); i++){
		for(int j = 0; j < this->multiplication.size(); j++){
			try{
				this->multiplication[i]->multiply(this->multiplication[j]);
				this->multiplication.erase(this->multiplication.begin()+j);
			}catch(Exceptions e){
				continue;
			}
		}
	}
}
void Expression::simplify(){
	/*
		Just simplify both vectors and call it a day
	*/
	this->add_simplify();
	this->multiply_simplify();
}

std::string Expression::toString(){
	/*
		If we only have our initial value, let's just return it in string form.
	*/
	if(!this->initialized){
		return this->value->toString();
	}

	int c	=	this->addition.size();
	std::string	result	=	"";

	/*
		Handle addition
	*/
	for(int i = 0; i < c; i++){
		/*
			If we have multiple addition elements, it's a good idea to wrap them in parentheses.
		*/
		if(i == 0 && c > 1){
			result += "(";
		}
		result	+=	this->addition[i]->toString();
		/*
			Add an addition symbol after our element as long as it isn't the last one in the vector.
		*/
		if(i < (c - 1)){
			result += " + ";
		}
		/*
			Close the parentheses when we're done.
		*/
		if(i == (c - 1) && c > 1){
			result += ")";
		}
	}

	/*
		If we have something to multiply by, put a multiplication symbol in between the two pieces of our string.
	*/
	if(!this->multiplication.empty()){
		result += " * ";
	}

	c	=	this->multiplication.size();

	for(int i = 0; i < c; i++){
		result	+=	this->multiplication[i]->toString();
		if(i < (c - 1)){
			result += " * ";
		}
	}
	return result;
}

double Expression::toDecimal(){
	this->simplify();

	int c	=	this->multiplication.size();
	double result	=	0;

	for(int i = 0; i < c; i++){
		result *= this->multiplication[i]->toDecimal();
	}

	c	=	this->addition.size();
	for(int i = 0; i < c; i++){
		result += this->addition[i]->toDecimal();
	}
	return result;
}

int Expression::getInt(){
	// Do nothing
}

Expression::~Expression(){
	//this->addition.clear();
	//this->multiplication.clear();
	//delete this;
}

std::string Expression::getName(){
	return "Expression";
}
