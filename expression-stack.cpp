#include <iostream>
#include <vector>
#include "expression.h"

using namespace std;

class expressionStack {

private:
   int top;
   vector<Expression*> items;

public:
	expressionStack(){
		top = -1;
	}

	~expressionStack(){}

	void push(Expression* expression){
		items.push_back(expression);
		top++;
	}

	Expression* pop(){
		if (isEmpty()){
			throw "Error with input! Operator to term ratio does not match up.";
		}
        else {
            return items.at(top--);
        }
	}

	Expression* getTop() {
        return items.at(top);
	}

	bool hasItems() {
        if (top>-1) {return true;}
        else return false;
	}

	int isEmpty(){ return top == -1; }
};
