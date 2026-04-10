#include "TVisitor.h"
#include <iostream>


Number::Number(int _val) : val(_val) {}
int Number::getVal() { return val; }
int Number::accept(TVisitor* v) { return v->visitNumber(this); }





BiOperation::BiOperation(string _op, Expr* _left, Expr* _right) : op(_op), left(_left), right(_right) {}
Expr* BiOperation::Left() { return this->left; }
Expr* BiOperation::Right() { return this->right; }
string BiOperation::Op() { return op; }
int BiOperation::accept(TVisitor* v) { return v->visitBiOperation(this); }
BiOperation::~BiOperation() {
	delete left;
	delete right;
}




int PrintVisitor::visitNumber(Number* num) {
	std::cout << num->getVal();
	return 0;
}
int PrintVisitor::visitBiOperation(BiOperation* op) {
	std::cout << "(";
	op->Left()->accept(this);
	std::cout << op->Op();
	op->Right()->accept(this);
	std::cout << ")";
	return 0;
}



int CalcVisitor::visitNumber(Number* num) {
	return num->getVal();
}
int CalcVisitor::visitBiOperation(BiOperation* op) {
	int left = op->Left()->accept(this);
	int right = op->Right()->accept(this);
	string operation = op->Op();
	int val;
	if (operation == "+") {
		val = left + right;
	}
	else if (operation == "-") {
		val = left - right;
	}
	else if (operation == "*") {
		val = left * right;
	}
	else {
		if (right == 0) throw runtime_error("div by 0");
		val = left / right;
	}
	return val;
}