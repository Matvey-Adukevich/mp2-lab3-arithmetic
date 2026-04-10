#pragma once

#include "tqueue.h"
#include "tstack.h"
#include <TVisitor.h>
#include <string>
#include <vector>
#include <map>

using namespace std;


class TArithmeticExpression {
	string infix;
	TQueue<string> postfix;
	TQueue<string> lexems;
	map<char, int> priority;
	map<char, double> operands;
	bool isCorrect;

	void Parse();
	void ToPostfix();
public:
	TArithmeticExpression();
	TArithmeticExpression(string infix);
	string GetInfix();
	string GetPostfix();
	TQueue<string> GetPostfixQueue();
	Expr* MakeTree();
	vector<char> GetOperands() const;
	double Calculate(const map<string, double>& values);

};

