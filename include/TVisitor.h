#pragma once
#include <string>

using namespace std;

class Number;
class BiOperation;
class TVisitor {
public:
	virtual int visitNumber(Number* num) = 0;
	virtual int visitBiOperation(BiOperation* op) = 0;
};

class Expr {
public:
	virtual int accept(TVisitor* v) = 0;
	virtual ~Expr() {}
};


class Number : public Expr {
	int val;
public:
	Number(int _val);
	int getVal();
	int accept(TVisitor* v);
	~Number() {}
};

class BiOperation : public Expr {
	string op;
	Expr* left, * right;
public:
	BiOperation(string _op, Expr* _left, Expr* _right);
	Expr* Left();
	Expr* Right();
	string Op();
	int accept(TVisitor* v);
	~BiOperation();
};

class PrintVisitor : public TVisitor {
public:
	int visitNumber(Number* num);
	int visitBiOperation(BiOperation* op);
};

class CalcVisitor : public TVisitor {
public:
	int visitNumber(Number* num);
	int visitBiOperation(BiOperation* op);
};


