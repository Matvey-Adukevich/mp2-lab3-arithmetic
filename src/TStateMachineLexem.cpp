#include "TStateMachineLexem.h"
#include "tqueue.h"
#include <functional>
#include <iostream>


TStateMachineLexem::Signal TStateMachineLexem::getSignal(char s) {
	if (s >= '0' && s <= '9') return Number;
	if (s == '+' || s == '-' || s == '*' || s == '/' || s == '(' || s == ')') return OperatorBracket;
	return Error;
}

void TStateMachineLexem::has_first_number(char c){
	buffer = c;
}
void TStateMachineLexem::has_operator(char c) {
	output.push(string(1,c));
}
void TStateMachineLexem::has_other_number(char c) {
	buffer += c;
}
void TStateMachineLexem::has_number_and_operator(char c) {
	if (!buffer.empty()) {
		output.push(buffer);
		buffer.clear();
	}
	output.push(string(1, c));
}
void TStateMachineLexem::has_error(char c) {
	throw runtime_error("Error state");
}



TQueue<string> TStateMachineLexem::parseWithFiniteAutomatonOrThrow() {
	buffer.clear();
	for (int i = 0; i < this->input.length(); i++) {
		Signal current_signal = getSignal(input[i]);
		State new_state = transitionTable[current_state][current_signal].new_state;
		transition_callback worker = transitionTable[current_state][current_signal].worker;
		if (worker != NULL) {
			worker(input[i]);
		}
		current_state = new_state;
	}
	if (current_state == S1 && !buffer.empty()) {
		output.push(buffer);
		buffer.clear();
	}
	return this->output;
}



TStateMachineLexem::TStateMachineLexem(const string& _input) :input(_input), current_state(S0) {
	transitionTable = {
	{S0, {{Number, {S1,[this](char c) {has_first_number(c); } }},{OperatorBracket, {S0, [this](char c) {has_operator(c); }}},{Error, {S2, [this](char c) {has_error(c); } }}}},
	{S1, {{Number, {S1, [this](char c) {has_other_number(c); } }},{OperatorBracket, {S0, [this](char c) {has_number_and_operator(c); }}},{Error, {S2, [this](char c) {has_error(c); }}}}}
	};
}

