#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include "expression.h"
#include <iostream>

class Parser {
    public:
        Parser();
        Parser(std::string);
        std::string parse(std::string);
        std::string input;
        std::string last_ans;
        std::string shunting_yard(std::string);

    private:
        bool isOperator(std::string);
        bool isLeftAsso(std::string);
        int getPrecedence(std::string);
        int checkPrecedence(std::string, std::string);
        Expression calculateFromRpn(std::string);
        int getNumberOfCharacters(int, int, int);

};


#endif // PARSER_H_INCLUDED
