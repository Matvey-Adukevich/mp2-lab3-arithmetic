#include "TArithmeticExpression.h"
#include "tqueue.h"
#include "tstack.h"
#include <map>
#include <string>
#include "TStateMachineLexem.h"

using namespace std;

TArithmeticExpression::TArithmeticExpression(string _infix) :infix(_infix) {
	priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0} };
	Parse();
	ToPostfix();
}

void TArithmeticExpression::Parse() {
// тут будут и конечные автоматы, и проверка на правильность и корректность, итог -> получаем очередь из лексем в виде инфиксной формы
	TStateMachineLexem machine(this->infix);
	this->lexems = machine.parseWithFiniteAutomatonOrThrow();
	
}

void TArithmeticExpression::ToPostfix() {
	TStack<string> stack(100);
	TQueue<string> lexems_copy = lexems;
	//postfix = "";

	while (!lexems_copy.isEmpty()) {
		string item = lexems_copy.pop();

		if (item == "(") {
			stack.push(item);
		}
		else if (item == ")") {
			while (!stack.isEmpty() && stack.top() != "(") {
				postfix.push(stack.pop());
			}
			stack.pop();
		}
		else if (item == "+" || item == "-" || item == "*" || item == "/") {
			while (!stack.isEmpty() && priority[stack.top()[0]] >= priority[item[0]]) {
				postfix.push(stack.pop());
			}
			stack.push(item);
		}
		else {
			postfix.push(item);
		}
	}
	while (!stack.isEmpty()) {
		postfix.push(stack.pop());
	}
}

string TArithmeticExpression::GetInfix() {
	return infix;
}

string TArithmeticExpression::GetPostfix() {
	string result = "";
	TQueue<string> temp = postfix;

	while (!temp.isEmpty()) {
		if (!result.empty()) result += " ";
		result += temp.pop();
	}
	return result;
}

TQueue<string> TArithmeticExpression::GetPostfixQueue() {
	return postfix;
}

double TArithmeticExpression::Calculate(const map<string, double>& values) {
	TStack<double> stack(100);
	TQueue<string> temp_postfix = postfix;

	while (!temp_postfix.isEmpty()) {
		string item = temp_postfix.pop();
		
		if (item == "+" || item == "-" || item == "*" || item == "/") {
			double b = stack.pop();
			double a = stack.pop();
			if (item == "+") {
				stack.push(a + b);
			}
			else if (item == "-") {
				stack.push(a - b);
			}
			else if (item == "*") {
				stack.push(a * b);
			}
			else if (item == "/") {
				stack.push(a / b);
			}
		}
		else {
			stack.push(stod(item));
		}
	
	}
	return stack.pop();

}
