#pragma once

template<typename T>
class TStack
{
protected:
	int curr;//вершина стека
	size_t n;//максимальное количество элементов в стеке
	T* mem;
public:
	TStack(size_t _n) {
		curr = -1;
		n = _n;
		mem = new T[n];
	}

	TStack(const TStack& stack) {
		curr = stack.curr;
		n = stack.n;
		mem = new T[n];
		for (size_t i = 0; i <= curr; i++) {
			mem[i] = stack.mem[i];
		}
	}

	~TStack() {
		delete[] mem;
	}

	bool isEmpty() {
		return curr < 0;
	}

	bool isFull() {
		return curr == n - 1;
	}

	TStack& operator=(const TStack& stack) {
		if (this == &stack) return *this;
		curr = stack.curr;
		n = stack.n;
		delete[] mem;
		mem = new T[n];
		for (size_t i = 0; i <= curr; i++) {
			mem[i] = stack.mem[i];
		}
		return *this;
	}

	void push(const T& elem) {
		if (curr == n - 1) throw "Not enough places at stack";
		curr++;
		mem[curr] = elem;
	}

	T& pop() {
		if (curr < 0) throw "Empty stack";
		return mem[curr--];
	}

	T& top() {
		if (curr < 0) throw "Empty stack";
		return mem[curr];
	}

};