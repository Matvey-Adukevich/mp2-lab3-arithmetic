#pragma once

template<typename T>
class TQueue 
{
protected:
	size_t n;//максимально возможное число элементов в очереди
	size_t s, f;//индекс начала и конца очереди
	T* mem;
public:
	size_t next(size_t i) {
		return (i + 1) % n;
	}

	TQueue() : n(100), s(0), f(n-1) {
		mem = new T[n];
	}

	TQueue(size_t _n) {
		n = _n;
		mem = new T[n];
		s = 0;
		f = n - 1;
	}

	TQueue(const TQueue& queue) {
		n = queue.n;
		s = queue.s;
		f = queue.f;
		mem = new T[n];
		for (size_t i = s; i != next(f); i = next(i)) {
			mem[i] = queue.mem[i];
		}
	}
	~TQueue() {
		delete[] mem;
	}

	bool isEmpty() {
		return s == next(f);
	}

	bool isFull() {
		return s == next(next(f));
	}

	void push(T elem) {
		if (isFull()) throw "Queue is full";
		f = next(f);
		mem[f] = elem;
	}

	T pop() {
		if (isEmpty()) throw "Empty queue";
		T res = mem[s];
		s = next(s);
		return res;
	}

	TQueue& operator=(const TQueue& queue) {
		if (this == &queue) return *this;
		n = queue.n;
		s = queue.s;
		f = queue.f;
		delete[] mem;
		mem = new T[n];
		if (f < s) {
			for (size_t i = s; i < n; i++) {
				mem[i] = queue.mem[i];
			}
			for (size_t i = 0; i <= f; i++) {
				mem[i] = queue.mem[i];
			}
		}
		else {
			for (size_t i = s; i <= f; i++) {
				mem[i] = queue.mem[i];
			}
		}
		return *this;
	}


};