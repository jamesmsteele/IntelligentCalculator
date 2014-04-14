#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>
using namespace std;

class Exceptions {
public:
	//Values
	int errorID;
	string errorName;

	//Constructor
	Exceptions();
	Exceptions(string errorName);

	//Destructor
	~Exceptions() {
	};

	//Methods
	void determineError(string errorName);

	int what();
	string whatString();



};

#endif /* EXCEPTIONS_H_ */
