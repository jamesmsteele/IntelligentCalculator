#include <vector>
#include <iostream>
#include "history.h"

using namespace std;

History::History(){

}

void History::print(){
	cout << this->ans() << endl;
}

void History::print(int start, int end){
	for(int i = start; i <= end; i++){
		cout << "Answer " << end - i  + 1 << ": " << this->history[i] << endl;
	}
}

void History::print(int start){
	int end	=	this->history.size() - 1;
	this->print(start, end);
}

void History::printAll(){
	int end	=	this->history.size() - 1;
	this->print(0, end);
}

void History::add(string hist){
	this->history.push_back(hist);
}

string History::ans(){
	if (!history.empty()) {
        return this->history.back();
	}
	else return "0";
}

string History::ans(int n){
	int size	=	this->history.size() - 1;
	return this->history[size - n];
}
