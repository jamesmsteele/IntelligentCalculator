#include <iostream>
using namespace std;

class operatorStack {

private:
   int MAX;
   int top;
   char* items;

public:
	operatorStack(int size){
		MAX = size;
		top = -1;
		items = new char[MAX];
	}

	~operatorStack(){ delete [] items; }

	void push(char operand){
		if(isFull()){
			cout << "Stack Full!" << endl;
			exit(1);
		}

		items[++top] = operand;
	}

	char pop(){
		if(isEmpty()){
			cout << "Stack Empty!" << endl;
			exit(1);
		}

		return items[top--];
	}

	bool hasItems() {
        if (top>-1) {return true;}
        else return false;
	}

	int isEmpty(){ return top == -1; }

	int isFull(){ return top+1 == MAX; }
};
