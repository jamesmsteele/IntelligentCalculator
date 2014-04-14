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
		cout<<"pushtop: "<<top<<endl;
	}

	Expression* pop(){
		if (isEmpty()){
			throw "Error wHAHAHHAHAith input! Operator to term ratio does not match up.";
		}
        else {
            return items.at(top--);
        }
	}

	void post_pop() {
        items.pop_back();
	}

	Expression* getTop() {
        if (hasItems()) {
            return items.at(top);
        }
        else {throw "EMPTY";}
	}

	bool hasItems() {
        if (top>-1) {return true;}
        else return false;
	}

	int isEmpty(){ return top == -1; }
};
