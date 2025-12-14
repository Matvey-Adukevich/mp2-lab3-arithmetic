#include "tstack.h"
#include "tqueue.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	string expr = "(()(";
	TStack<int> stack(10);
	TQueue<int> queue(10);
	for (int i = 0; i < expr.length(); i++) {
		if (expr[i] == '(') {
			stack.push(i);
		}
		else {
			if (!stack.isEmpty()) {
				stack.pop();
			}
			else {
				queue.push(i);
			}
		}
	}
	if (!queue.isEmpty() || !stack.isEmpty()) {
		cout << "error";
	}
	TStack<int> stack_per(10);
	while (!stack.isEmpty()) {
		stack_per.push(stack.pop());
	}
	while (!stack_per.isEmpty()) {
		cout << stack_per.pop();
	}
	while (!queue.isEmpty()) {
		cout << queue.pop();
	}

}
