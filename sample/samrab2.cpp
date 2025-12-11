#include "tstack.h"
#include <iostream>

using namespace std;

int main() {
	int arr[7] = {2, 5, 4, 3, 10, 3, 1};
	int res_arr[7];
	TStack<int> stack(10);
	stack.push(-1);
	for (int i = 0; i < 7; i++) {
		while (!stack.isEmpty() && stack.top() != -1 && arr[stack.top()] >= arr[i]) {
			stack.pop();
		}

		res_arr[i] = stack.top();
		stack.push(i);
	}
	cout << "[";
	for (int i = 0; i < 7; i++) {
		cout << res_arr[i]<<" ";
	}
	cout << "]";

}