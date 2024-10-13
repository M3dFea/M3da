#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <cmath>
//Hearder file for Parse 
//operations supported +,-,/,*,^

//define the predence of the numerial operator
int precedence(char op);
//perform the operation on a & b
double applyOp(double a, double b, char op);
//parse the supplied numerical string
bool isOp(char op);
bool isOp2(char op);
bool isPartofNumber(std::string expression, int iC);
double evaluate(std::string expression);