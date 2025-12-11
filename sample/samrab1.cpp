#include "tstack.h"
#include "tqueue.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	string expr = "(()(";
	TStack<int> stack(10);
	TQueue<int> stack2(10);
	for (int i = 0; i < expr.length(); i++) {
		if (expr[i] == '(') {
			stack.push(i);
		}
		else {
			if (!stack.isEmpty()) {
				stack.pop();
			}
			else {
				stack2.push(i);
			}
		}
	}
	while (!stack.isEmpty()) {
		stack2.push(stack.pop());
	}
	if (!stack2.isEmpty()) {
		cout << "error";
	}
	while (!stack2.isEmpty()) {
		cout << stack2.pop();
	}

}
