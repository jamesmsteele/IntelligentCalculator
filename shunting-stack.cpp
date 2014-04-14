#include <iostream>
#include <exception>
using namespace std;

class shuntingStack {

private:
   int MAX;
   int top;
   string* items;

public:
	shuntingStack(int sizey){
		MAX = sizey;
		top = -1;
		items = new string[MAX];
	}

	~shuntingStack(){ delete [] items; }

	void push(string c){
		if(isFull()){
			cout << "Stack Full!" << endl;
		}

		items[++top] = c;
	}

	string pop(){
		if(isEmpty()){
			throw "Error with input! Operator to term ratio does not match up.";
		}
        else {
            return items[top--];
        }
	}

	string getTop() {
        return items[top];
	}

	bool hasItems() {
        if (top>-1) {return true;}
        else return false;
	}

	int isEmpty(){ return top == -1; }

	int isFull(){ return top+1 == MAX; }
};
