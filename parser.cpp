#include "Parser.h"
#include "shunting-stack.cpp"
#include "expression-stack.cpp"
#include "exp-integer.h"
#include "fraction.h"
#include "exponent.h"
#include "euler.h"
#include "pi.h"
#include <vector>
#include <ctype.h>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <exception>
#include <stdio.h>

Parser::Parser(){
	input		=	" ";
	last_ans	=	"0";
}

Parser::Parser(std::string input){
	this->input	=	input;
	last_ans	=	"0";
}
std::string Parser::parse(std::string input){
	return this->calculateFromRpn(shunting_yard(input)).toString();
}

bool Parser::isOperator(std::string potentialOperator){
	if(potentialOperator.compare("+") == 0 || potentialOperator.compare("-") == 0
	|| potentialOperator.compare("*") == 0 || potentialOperator.compare("/") == 0
	|| potentialOperator.compare("^") == 0){
		return true;
	}else{
		return false;
	}
}

// What is this method?
bool Parser::isLeftAsso(std::string c){
	if (c.compare("^") != 0) {
		return true;
	}else{
		return false;
	}
}

int Parser::getPrecedence(std::string op) {
	if(op.compare("^") == 0){
		return 4;
	}else if(op.compare("*") == 0 || op.compare("/") == 0){
		return 3;
	}else if(op.compare("+") == 0 || op.compare("-") == 0){
		return 2;
	}else{
		return 0;
	}
}

int Parser::checkPrecedence(std::string operator1, std::string operator2){
	int operator1precedence	=	0;
	int operator2precedence	=	0;
	operator1precedence = this->getPrecedence(operator1);
	operator2precedence = this->getPrecedence(operator2);

	if(operator1precedence < operator2precedence){
		return -1;
	}else if(operator1precedence > operator2precedence){
		return 1;
	}else{
		return 0;
	}
}

int Parser::getNumberOfCharacters(int numberOfCharacters, int prelen, int position) {
	int openParenthesis			=	1;
	int closeParenthesis		=	0;
	int hasSpace				=	0;
	unsigned int inputLength	=	this->input.length();

	if(input[position+prelen-1] == ' '){
		hasSpace	=	1;
	}
	for (unsigned int p = hasSpace; p < (inputLength - position - prelen); p++){
		if((input.substr(position + p + prelen, 1)).compare("(") == 0){
			openParenthesis++;
			std::cout << "Open: " << openParenthesis << endl;
		}else if((input.substr(position + p + prelen, 1)).compare(")") == 0){
			closeParenthesis++;
			std::cout << "Closed: " << closeParenthesis << endl;
		}if(closeParenthesis == openParenthesis){
			//exit out
			numberOfCharacters	=	p;
			p					=	inputLength - position;
		}
	}
	return numberOfCharacters;
}

Expression Parser::calculateFromRpn(std::string input) {
	cout << "input: " << input << endl;
	unsigned int j				=	0;
	unsigned int inputLength	=	this->input.length();
	int numberOfDigits			=	0;
	expressionStack expStack;

	while (j < input.length()){
		if ((input.substr(j,2)).compare("pi") == 0) {
            Pi* pipi = new Pi();
            expStack.push(pipi);
            j += 2;
		}
		else if ((input.substr(j,1)).compare("e") == 0) {
            Eulers* ee = new Eulers();
            expStack.push(ee);
            j++;
		}
		/*
			Let's check if our value is a single number
			We also check if the previous character is an underscore, which indicates that it's the b in log_b:a
		*/
		else if(isdigit(input[j]) && input[j - 1] != '_' && input[j + 1] != 'r' && input[j + 1] != 'R'){
			/*
				We'll use this variable to track the length of this expression so that we can skip ahead to the next one when we're done
			*/
			numberOfDigits = 0;

			/*
				Next, we'll calculate how many digits are in our number
			*/
			while(isdigit(input[j + numberOfDigits + 1])){
				numberOfDigits++;
			}

			/*
				Our number spans from j to numberOfDigits + 1, so we can take the substring of that range to get our number
			*/
			std::string number	=	input.substr(j, numberOfDigits + 1);

			/*
				If our number is negative, let's add a negative sign in front of it
			*/
			if(input[j-1] == '-'){
				number	=	"-" + number;
			}

			std::cout << "Numdetect: " << number << endl;

			/*
				Our number is currently a string, so let's use atoi to cast it as an int, then dump it into a MathExInt object
			*/
			int numberAsInt		=	atoi(number.c_str());
			MathExInteger* num	=	new MathExInteger(numberAsInt);

			/*
				Now we can push our integer onto our expression stack
			*/
			std::cout << "NUM: " + num->toString() << endl;
			expStack.push(num);
			std::cout << "NUM: " + expStack.getTop()->toString() << endl;

			/*
				Finally, we can increment j by the number of digits we've encountered
			*/
			j += numberOfDigits + 1;
			std::cout << "Inputj: " << j << endl;
		}
		else if(input[j] == ' '){
            /*
                If we encounter a space, we can just jump right over it
            */
			j++;
			std::cout << "Inputj: " << j << endl;
		}
		/*
			substr(j, 5) gets the next 5 characters in our input string
			We'll check if it's equal to "sqrt:", which means that we need to create a square root object
		*/
		else if((input.substr(j, 5)).compare("sqrt:") == 0){
			/*
				Like before, we'll use this variable to track the size of our expression
				Then we'll find how big it is
			*/
			numberOfDigits = 0;
			while(isdigit(input[j + numberOfDigits + 6])){
				numberOfDigits++;
			}

			/*
				Let's put our number into a string then cast it into an int (radical)
			*/
			std::string number	=	input.substr(j + 5, numberOfDigits + 1);
			int radical			=	atoi(number.c_str());
			/*
				Let's create an int out of our radical
				Let's also create a coefficient
			*/
			MathExInteger* newRadical		=	new MathExInteger(radical);
			MathExInteger* newCoefficient	=	new MathExInteger(1);
			/*
				Let's create a fraction equal to 1/2
			*/
			MathExInteger* one				=	new MathExInteger(1);
			MathExInteger* two				=	new MathExInteger(2);
			try{
				Fraction* half					=	new Fraction(one, two);
			}catch(Exceptions ex){
				/*
					Remember to handle fraction errors here too
				*/
			}
			Fraction* half					=	new Fraction(one, two);

			/*
				Now we can create an exponent with our coefficient, radical, and a power of 1/2 and put it on our stack
			*/
			try{
				Exponent* sq					=	new Exponent(newCoefficient, newRadical, half);
				expStack.push(sq);
			}catch(Exceptions e){
				int error	=	e.what();
				switch(error){
					case 4:{
						throw "Invalid log expression";
						break;
					}
					case 6:{
						break;
					}
					case 16:{
						MathExInteger* case16	=
							new MathExInteger(pow(newRadical->toDecimal(),half->toDecimal()));
						case16->multiply(newCoefficient);
						expStack.push(case16);
						break;
					}
				}
				char a;
				cout << e.whatString() << endl;
				cout << e.what() << endl;
				cout << expStack.getTop()->toString() << endl;
				cin >> a;
			}

			/*
				As before, let's increment our iterator by the length of our sqrt token
			*/
			j += numberOfDigits+5;
		}
		/*
			nth roots are similar to sqrts, but we need to create a custom fraction for our power
		*/
		else if((input.substr(j+1, 3)).compare("rt:") == 0){
			numberOfDigits = 0;
			while(isdigit(input[j + numberOfDigits + 4])) {
				numberOfDigits++;
			}
			int n				=	atoi((input.substr(j, j + 1)).c_str());
			std::string number	=	input.substr(j + 4, j + numberOfDigits + 4);
			int radical			=	atoi(number.c_str());
			std::vector<Expression*> frac;

			MathExInteger* newRadical		=	new MathExInteger(radical);
			MathExInteger* newCoefficient	=	new MathExInteger(1);
			MathExInteger* one				=	new MathExInteger(1);
			MathExInteger* newN				=	new MathExInteger(n);

			try{
				Fraction* f					=	new Fraction(one, newN);
				frac.push_back(f);
			}catch(Exceptions ex){
				switch(ex.what()){
					case 1:
						throw "Cannot divide by 0";
						break;
					case 3:{
						MathExInteger* f	=	new MathExInteger(1);
						frac.push_back(f);
						break;
					}
					default:{
						Fraction* f			=	new Fraction(one, newN);
						frac.push_back(f);
					}
				}
			}

			try{
				Exponent* nr					=	new Exponent(newCoefficient, newRadical, frac.back());
				expStack.push(nr);
			}catch(Exceptions e){
				int error	=	e.what();
				switch(error){
					case 4:{
						throw "Invalid expression";
						break;
					}
					case 6:{
						break;
					}
					case 16:{
						MathExInteger* case16	=
							new MathExInteger(pow(newRadical->toDecimal(),frac.back()->toDecimal()) + .5);
						case16->multiply(newCoefficient);
						expStack.push(case16);
						break;
					}
					case 22:{
						MathExInteger* case22	=	new MathExInteger(newRadical->toDecimal() + .5);
						case22->multiply(newCoefficient);
						expStack.push(case22);
						break;
					}
					case 23:{
						MathExInteger* case23	=	new MathExInteger(0);
						expStack.push(case23);
						break;
					}
					case 21:{
						MathExInteger* case21	=	new MathExInteger(1);
						case21->multiply(newCoefficient);
						expStack.push(case21);
						break;
					}
				}
				cout << e.whatString() << endl;
				cout << e.what() << endl;
			}
			j	+=	numberOfDigits + 4;
		}
		/*
			Next, let's see if we've found a logarithm
		*/
		else if((input.substr(j, 6)).compare("log_e:") == 0){
			cout << "loge detected" << endl;
			/*
				As always, let's find the length of our arguments
			*/
			numberOfDigits = 0;
			while (isdigit(input[j+numberOfDigits+7])) {
				numberOfDigits++;
			}

			/*
				First, let's find our argument
			*/
			int arg					=	atoi((input.substr(j + 6, numberOfDigits + 1)).c_str());

			MathExInteger* newCoefficient	=	new MathExInteger(1);
			Eulers* newBase			        =	new Eulers();
			MathExInteger* newArg			=	new MathExInteger(arg);

			try{
				Logarithm* result				=	new Logarithm(newCoefficient, newBase, newArg);
				expStack.push(result);
			}catch(Exceptions e){
				int error	=	e.what();

				switch(error){
					case 4:{
						throw "Invalid expression";
						break;
					}
					case 5:{
						throw "Invalid expression";
						break;
					}
					case 6:{
						MathExInteger* case6	=	new MathExInteger(0);
						case6->multiply(newCoefficient);
						expStack.push(case6);
						break;
					}
					case 12:{
						MathExInteger* case12	=
							new MathExInteger(log10(newArg->toDecimal())/log10(newBase->toDecimal()));
						case12->multiply(newCoefficient);
						expStack.push(case12);
						break;
					}
				}
			}
			j  +=	numberOfDigits + 7;
		}  else if((input.substr(j, 7)).compare("log_pi:") == 0){
			cout << "logpi detected" << endl;
			/*
				As always, let's find the length of our arguments
			*/
			numberOfDigits = 0;
			while (isdigit(input[j+numberOfDigits+7])) {
				numberOfDigits++;
			}

			/*
				First, let's find our argument
			*/
			int arg					=	atoi((input.substr(j + 6, numberOfDigits + 1)).c_str());

			MathExInteger* newCoefficient	=	new MathExInteger(1);
			Pi* newBase			            =	new Pi();
			MathExInteger* newArg			=	new MathExInteger(arg);

			try{
				Logarithm* result				=	new Logarithm(newCoefficient, newBase, newArg);
				expStack.push(result);
			}catch(Exceptions e){
				int error	=	e.what();

				switch(error){
					case 4:{
						throw "Invalid expression";
						break;
					}
					case 5:{
						throw "Invalid expression";
						break;
					}
					case 6:{
						MathExInteger* case6	=	new MathExInteger(0);
						case6->multiply(newCoefficient);
						expStack.push(case6);
						break;
					}
					case 12:{
						MathExInteger* case12	=
							new MathExInteger(log10(newArg->toDecimal())/log10(newBase->toDecimal()));
						case12->multiply(newCoefficient);
						expStack.push(case12);
						break;
					}
				}
			}
			j  +=	numberOfDigits + 8;
		} else if((input.substr(j, 4)).compare("log_") == 0){
			std::cout << "log detected" << endl;
			/*
				As always, let's find the length of our arguments
			*/
			numberOfDigits = 0;
			while (isdigit(input[j+numberOfDigits+7])) {
				numberOfDigits++;
			}

			/*
				First, let's find our argument
			*/
			int arg					=	atoi((input.substr(j + 6, numberOfDigits + 1)).c_str());

			/*
				Second, let's find our base
			*/
			std::string base_str	=	input.substr(j + 4, 1);
			int base				=	atoi(base_str.c_str());

			MathExInteger* newCoefficient	=	new MathExInteger(1);
			MathExInteger* newBase			=	new MathExInteger(base);
			MathExInteger* newArg			=	new MathExInteger(arg);

			try{
				Logarithm* result				=	new Logarithm(newCoefficient, newBase, newArg);
				expStack.push(result);
			}catch(Exceptions e){
				int error	=	e.what();

				switch(error){
					case 4:{
						throw "Invalid expression";
						break;
					}
					case 5:{
						throw "Invalid expression";
						break;
					}
					case 6:{
						MathExInteger* case6	=	new MathExInteger(0);
						case6->multiply(newCoefficient);
						expStack.push(case6);
						break;
					}
					case 12:{
						MathExInteger* case12	=
							new MathExInteger(log10(newArg->toDecimal())/log10(newBase->toDecimal()));
						case12->multiply(newCoefficient);
						expStack.push(case12);
						break;
					}
				}
			}
			j  +=	numberOfDigits + 7;
		}
		else{
		    std::cout<< "LOOKIN FOR OPERATORS SIR" << endl;
			/*
				Let's see if we're dealing with a negative number
			*/
			if (input[j] == '-' && isdigit(input[j + 1])) {
				j++;
			}else{
			/*
				Now we can look for an operator (+,-,*,/,^)
			*/
				std::vector<Expression*> expression1;
				std::vector<Expression*> expression2;
				try {
					expression1.push_back(expStack.pop());
					expStack.post_pop();
				}
				catch (const char* e) {
					throw e;
				}

				try {
					expression2.push_back(expStack.pop());
					expStack.post_pop();
				}
				catch (const char* e) {
					throw e;
				}
				std::cout<<"A:"<<expression1.back()->toString()<<" "<<input[j]<<" B:"<<expression2.back()->toString()<<endl;

				switch(input[j]){
					case '+':
						try {
                            expression1.back()->add(expression2.back());
                            expStack.push(expression1.back());
                        } catch (Exceptions e) {
                            int error = e.what();
                            cout << e.whatString() << endl;
                            switch (error) {
                            case 14:
                            case 7:
                            case 27:
                                Expression* addexp = new Expression(expression1.back());
                                addexp->add(expression2.back());
                                cout << addexp->toString() << endl;
                                addexp->simplify();
                                cout << addexp->toString() << endl;
                                expStack.push(addexp);
                                break;
                            }
                        }
						break;
					case '-':
						try {
                            expression2.back()->subtract(expression1.back());
                            expStack.push(expression2.back());
                        } catch (Exceptions e) {
                            int error = e.what();
                            cout << e.whatString() << endl;
                            switch (error) {
                            case 15:
                            case 8:
                            case 28:
                                Expression* subexp = new Expression(expression2.back());
                                subexp->subtract(expression1.back());
                                subexp->simplify();
                                cout << subexp->toString() << endl;
                                expStack.push(subexp);
                                break;
                            }
                        }
						break;
					case '*':
						try {
                            expression2.back()->multiply(expression1.back());
                            expStack.push(expression2.back());
                        } catch (Exceptions e) {
                            int error = e.what();
                            cout << e.whatString() << endl;
                            switch (error) {
                            case 17:
                            case 10:
                            case 29:
                                Expression* mulexp = new Expression(expression2.back());
                                mulexp->multiply(expression1.back());
                                mulexp->simplify();
                                cout << mulexp->toString() << endl;
                                expStack.push(mulexp);
                                break;
                            }
                        }
						break;
					case '/':
						try {
                            expression2.back()->divide(expression1.back());
                            expStack.push(expression2.back());
                        } catch (Exceptions e) {
                            int error = e.what();
                            cout << e.whatString() << endl;
                            switch (error) {
                            case 16:
                            case 9:
                            case 30:
                                Expression* divexp = new Expression(expression2.back());
                                divexp->divide(expression1.back());
                                divexp->simplify();
                                expStack.push(divexp);
                                break;
                            }
                        }
					case '^':
						Expression* base	=	new Expression(expression2.back());
						Expression* exp		=	new Expression(expression1.back());
						Expression* one		=	new MathExInteger(1);
						Exponent* expo		=	new Exponent(one, base, exp);
						expStack.push(expo);
						break;
					}
				j++;
			}
		}
	}
	std::cout<<"Top: "<<expStack.getTop()->toString()<<endl;
	return expStack.getTop();
}

std::string Parser::shunting_yard(std::string input) { //CODED BY OURSELVES NO COPY PASTING
    if((input.length()) < 1){
        throw "Please input an expression.";
    }
    unsigned int i		=	0;
    int num_left_paren	=	0;
    std::string output	=	"";

    shuntingStack sh_stack(100);

    while (i < input.length()){
        if (isdigit(input[i]) && input[i + 1] != ':' && input[i + 1] != 'r'){
            int num_digits	=	0;
            output.append(1, input[i]);
            while(isdigit(input[i + num_digits + 1])){
                output.append(1, input[i + num_digits + 1]);
                num_digits++;
            }
            i	+=	num_digits+1;
            output.append(" ");
        }
        else if(isOperator(input.substr(i, 1))){
            if (input[i]=='-' && isdigit(input[i + 1])){ //&& input[i-1]==' ') { //negative number i.e. 5 + -24
                i++;
                output.append("-");
            }
            else {
                while(!sh_stack.isEmpty()				&&
					isOperator(sh_stack.getTop())		&&
					((isLeftAsso(input.substr(i, 1))	&&
					checkPrecedence(input.substr(i, 1), sh_stack.getTop()) == 0) ||
					checkPrecedence(input.substr(i, 1), sh_stack.getTop()) == -1)
				){
                    output.append(sh_stack.pop());
                    output.append(" ");
                }
                sh_stack.push(input.substr(i, 1));
                i++;
            }
        }else if((input.substr(i, 1)).compare("(") == 0) {
            sh_stack.push(input.substr(i, 1));
            num_left_paren++;
            i++;
        }
        else if((input.substr(i, 1)).compare(")") == 0){
            if (num_left_paren > 0) {
                while((sh_stack.getTop()).compare("(") != 0) {
                    output.append(sh_stack.pop());
                    output.append(" ");
                }
                num_left_paren--;
                sh_stack.pop();
                i++;
            }
            else{
				throw "Error with parentheses! You must have parentheses in pairs.";
			}
        }
        else if((input.substr(i, 1)).compare(" ") == 0){
            i++;
        }
        else if((input.substr(i, 5)).compare("sqrt:") == 0){
            //sqrt:x
            if (input[i+5] == '-' || input[i+6] == '-'){
                throw "Negative square root detected. Imaginary numbers are not supported.";
            }
            int num_chars = 0;
            if(input[i+5]!='(' && input[i+6]!='(') { //not a sqrt:(x+y) expression
                while(input[i + num_chars + 1] != ' ' &&
				input[i + num_chars + 1] != ')' &&
				(i + num_chars + 1) < input.length()
				){ //gets number of digits of sqrt, i.e. sqrt:xxxxx
                    num_chars++;
                }
                output.append(input.substr(i, num_chars + 1));
                output.append(" ");
                i	+=	num_chars + 1;
            }
            else{ //is sqrt with parentheses
                num_chars		=	0;
                int open_paren	=	1;
                int close_paren	=	0;
                int has_space	=	0;

                if (input[i + 5] == ' '){
					has_space	=	1;
				}

                for(int p = has_space; p < (input.length() - i - 6); p++){ //get expression inside parentheses
                    if((input.substr(i + p + 6, 1)).compare("(") == 0){
                        open_paren++;
                        std::cout << "Open:" << open_paren << endl;
                    }
                    else if((input.substr(i + p  +6, 1)).compare(")") == 0){
                        close_paren++;
                        std::cout << "Closed:" << close_paren << endl;
                    }
                    if(close_paren == open_paren) {
                        //exit out
                        num_chars	=	p;
                        p			=	input.length() - i;
                    }
                }
                num_chars	=	getNumberOfCharacters(0, 6, i);
                std::cout << num_chars << endl;
                std::string eval	=	this->parse(input.substr(i + 5, num_chars + 2)); //parse expression inside ( and )
                eval				=	"sqrt:" + eval;
                output.append(eval);
                output.append(" ");
                i					+=	num_chars+7;
            }
        }
        else if((input.substr(i + 1, 3)).compare("rt:") == 0) {
            //nrt:x
            int num_chars	=	0;
            if (input[i + 4] != '(' && input[i + 5] != '('){ //not a nrt:(x+y) expression
                while (input[i + num_chars + 1] != ' ' && input[i + num_chars + 1] != ')' && (i + num_chars + 1) < input.length()){ //gets number of digits of nrt, i.e. nrt:xxxx
                    num_chars++;
                }
                output.append(input.substr(i, num_chars + 1));
                output.append(" ");
                i	+=	num_chars + 1;
            }
            else{ //is nrt with parentheses
                num_chars		=	0;
                int open_paren	=	1;
                int close_paren	=	0;
                int has_space	=	0;
                if (input[i + 5] == ' '){
					has_space = 1;
				}
                for(int p = has_space; p < input.length() - i - 5; p++){ //get expression inside parentheses
                    if ((input.substr(i + p + 5, 1)).compare("(") == 0){
                        open_paren++;
                        std::cout << "Open:" << open_paren << endl;
                    }
                    else if((input.substr(i + p + 5, 1)).compare(")") == 0){
                        close_paren++;
                        std::cout << "Closed:" << close_paren << endl;
                    }
                    if(close_paren == open_paren){
                        //exit out
                        num_chars	=	p;
                        p			=	input.length() - i;
                    }
                }
                std::cout << input.substr(i + 4, num_chars + 2) << endl;
                std::string eval = parse(input.substr(i + 4, num_chars + 2)); //parse expression inside ( and )
                std::cout << eval << endl;
                eval	=	input.substr(i, 1)+"rt:"+eval;
                std::cout << eval << endl;
                output.append(eval);
                output.append(" ");
                i		+=	num_chars+6;
            }
        }
        else if((input.substr(i, 4)).compare("log_") == 0){
            //log_b:x
            int num_chars	=	0;
            if(input[i + 6] != '(' && input[i + 7] != '('){ //not a log_b:(x+y) expression
                while(input[i + num_chars + 1] != ' ' && input[i + num_chars + 1] != ')' && (i + num_chars + 1) < input.length()){ //gets number of digits of nrt, i.e. nrt:xxxx
                    num_chars++;
                }
                output.append(input.substr(i, num_chars + 1));
                output.append(" ");
                i	+=	num_chars + 1;
            }
            else{ //is log_b:() with parentheses
                num_chars		=	0;
                int open_paren	=	1;
                int close_paren	=	0;
                int has_space	=	0;
                if(input[i + 6] == ' '){
                        std::cout << "found space" << endl;
                        has_space	=	1;
				}
                for(int p = has_space; p < input.length() - i - 7; p++) { //get expression inside parentheses
                    if((input.substr(i + p + 7, 1)).compare("(") == 0){
                        open_paren++;
                        std::cout << "Open:" << open_paren << endl;
                    }
                    else if((input.substr(i + p + 7, 1)).compare(")") == 0){
                        close_paren++;
                        std::cout << "Closed:" << close_paren << endl;
                    }
                    if(close_paren == open_paren){
                        //exit out
                        num_chars	=	p;
                        p			=	input.length() - i;
                    }
                }
                std::cout << input.substr(i + 6, num_chars + 2) << endl;
                std::string eval	=	parse(input.substr(i + 6, num_chars + 2)); //parse expression inside ( and )
                std::cout << eval << endl;
                eval				=	input.substr(i, 6) + eval;
                std::cout << eval << endl;
                output.append(eval);
                output.append(" ");
                i					+=	num_chars + 8;
            }
            sh_stack.push(input.substr(i, 6));
            i+=6;
        } else if((input.substr(i, 6)).compare("log_e:") == 0){
            //log_b:x
            int num_chars	=	0;
            if(input[i + 6] != '(' && input[i + 7] != '('){ //not a log_b:(x+y) expression
                while(input[i + num_chars + 1] != ' ' && input[i + num_chars + 1] != ')' && (i + num_chars + 1) < input.length()){ //gets number of digits of nrt, i.e. nrt:xxxx
                    num_chars++;
                }
                output.append(input.substr(i, num_chars + 1));
                output.append(" ");
                i	+=	num_chars + 1;
            }
            else{ //is log_b:() with parentheses
                num_chars		=	0;
                int open_paren	=	1;
                int close_paren	=	0;
                int has_space	=	0;
                if(input[i + 6] == ' '){
                        std::cout << "found space" << endl;
                        has_space	=	1;
				}
                for(int p = has_space; p < input.length() - i - 7; p++) { //get expression inside parentheses
                    if((input.substr(i + p + 7, 1)).compare("(") == 0){
                        open_paren++;
                        std::cout << "Open:" << open_paren << endl;
                    }
                    else if((input.substr(i + p + 7, 1)).compare(")") == 0){
                        close_paren++;
                        std::cout << "Closed:" << close_paren << endl;
                    }
                    if(close_paren == open_paren){
                        //exit out
                        num_chars	=	p;
                        p			=	input.length() - i;
                    }
                }
                std::cout << input.substr(i + 6, num_chars + 2) << endl;
                std::string eval	=	parse(input.substr(i + 6, num_chars + 2)); //parse expression inside ( and )
                std::cout << eval << endl;
                eval				=	input.substr(i, 6) + eval;
                std::cout << eval << endl;
                output.append(eval);
                output.append(" ");
                i					+=	num_chars + 8;
            }
            sh_stack.push(input.substr(i, 6));
            i+=6;
        } else if((input.substr(i, 4)).compare("log_") == 0){
            //log_b:x
            int num_chars	=	0;
            if(input[i + 6] != '(' && input[i + 7] != '('){ //not a log_b:(x+y) expression
                while(input[i + num_chars + 1] != ' ' && input[i + num_chars + 1] != ')' && (i + num_chars + 1) < input.length()){ //gets number of digits of nrt, i.e. nrt:xxxx
                    num_chars++;
                }
                output.append(input.substr(i, num_chars + 1));
                output.append(" ");
                i	+=	num_chars + 1;
            }
            else{ //is log_b:() with parentheses
                num_chars		=	0;
                int open_paren	=	1;
                int close_paren	=	0;
                int has_space	=	0;
                if(input[i + 6] == ' '){
                        std::cout << "found space" << endl;
                        has_space	=	1;
				}
                for(int p = has_space; p < input.length() - i - 7; p++) { //get expression inside parentheses
                    if((input.substr(i + p + 7, 1)).compare("(") == 0){
                        open_paren++;
                        std::cout << "Open:" << open_paren << endl;
                    }
                    else if((input.substr(i + p + 7, 1)).compare(")") == 0){
                        close_paren++;
                        std::cout << "Closed:" << close_paren << endl;
                    }
                    if(close_paren == open_paren){
                        //exit out
                        num_chars	=	p;
                        p			=	input.length() - i;
                    }
                }
                std::cout << input.substr(i + 6, num_chars + 2) << endl;
                std::string eval	=	parse(input.substr(i + 6, num_chars + 2)); //parse expression inside ( and )
                std::cout << eval << endl;
                eval				=	input.substr(i, 6) + eval;
                std::cout << eval << endl;
                output.append(eval);
                output.append(" ");
                i					+=	num_chars + 8;
            }
            sh_stack.push(input.substr(i, 6));
            i+=6;
        }
        else if((input.substr(i, 3)).compare("ans") == 0){
            //user using last ans
            output.append(last_ans);
            output.append(" ");
            i	+=	3;
        }
        else if ((input.substr(i,2)).compare("pi") == 0) {
            output.append("pi ");
            i += 2;
        }
        else if ((input.substr(i,1)).compare("e") == 0) {
            output.append("e ");
            i += 1;
        }
        else {
            throw "Invalid expression detected in input. Please try again.";
        }
    }

    while (sh_stack.hasItems())
    {
        output.append(sh_stack.pop());
        output.append(" ");
    }
    std::cout<<output<<endl;
    return output;
}
