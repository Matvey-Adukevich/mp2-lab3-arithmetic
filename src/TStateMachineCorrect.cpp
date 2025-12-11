#include "TStateMachineCorrect.h"
#include "tqueue.h"
#include <functional>
#include <iostream>


TStateMachineCorrect::Signal TStateMachineCorrect::getSignal(string s) {
	if (s.empty()) return Error;
	if ('0' <= s[0] && s[0] <= '9') return Number;
	if (s == "+" || s == "-") return OperatorPlusMinus;
	if (s == "*" || s == "/") return OperatorMultDiv;
	if (s == "(") return BracketOpen;
	if (s == ")") return BracketClose;
	return Error;
}


void TStateMachineCorrect::has_number(string s) { this->buffer.push(s); }


void TStateMachineCorrect::has_open_bracket(string s) { this->stack.push(s); }



void TStateMachineCorrect::has_close_bracket(string s) { 
	if (stack.isEmpty()) {
		throw runtime_error("Closing bracket");
	}
	this->stack.pop();

}


void TStateMachineCorrect::has_plus_minus_operator(string s) { this->buffer.push(s); }


void TStateMachineCorrect::has_mult_div_operator(string s) { this->buffer.push(s); }



void TStateMachineCorrect::has_error(string s) { throw runtime_error("Error_state"); }

//void TStateMachineCorrect::has_first_number(char c) {
//	buffer = c;
//}
//void TStateMachineCorrect::has_operator(char c) {
//	output.push(string(1, c));
//}
//void TStateMachineCorrect::has_other_number(char c) {
//	buffer += c;
//}
//void TStateMachineCorrect::has_number_and_operator(char c) {
//	if (!buffer.empty()) {
//		output.push(buffer);
//		buffer.clear();
//	}
//	output.push(string(1, c));
//}
//void TStateMachineCorrect::has_error(char c) {
//	throw runtime_error("Error state");
//}



bool TStateMachineCorrect::parseWithFiniteAutomatonOrThrow() {
	/*buffer.clear();*/
	TQueue<string> queue_copy(this->input);
	while (!buffer.isEmpty()) {
		buffer.pop();
	}
	while(!queue_copy.isEmpty()) {
		string i = queue_copy.pop();
		Signal current_signal = getSignal(i);
		State new_state = transitionTable[current_state][current_signal].new_state;
		transition_callback worker = transitionTable[current_state][current_signal].worker;
		if (worker != NULL) {
			worker(i);
		}
		current_state = new_state;
	}
	//if (current_state == S1 && !buffer.isEmpty()) {
	//	while (!buffer.isEmpty()) {
	//		output.push(buffer.pop());
	//	}
		//output.push(buffer);
		//buffer.clear();
	//}
	if (current_state == S9 || !stack.isEmpty()) {
		return false;
	}
	return true;
}



TStateMachineCorrect::TStateMachineCorrect(const TQueue<string>& _input):input(_input), current_state(S0) {
	transitionTable = {
	{S0, {{Number, {S2,[this](string s) {has_number(s); } }},{BracketOpen, {S0, [this](string s) {has_open_bracket(s); }}},{BracketClose, {S9, [this](string s) {has_error(s); }}}, {OperatorPlusMinus, {S6, [this](string s) {has_plus_minus_operator(s); }}}, {OperatorMultDiv, {S9, [this](string s) {has_error(s); }}}, {Error, {S9, [this](string s) {has_error(s); }}}}},
	{S1, {{Number, {S2,[this](string s) {has_number(s); } }},{BracketOpen, {S0, [this](string s) {has_open_bracket(s); }}},{BracketClose, {S8, [this](string s) {has_close_bracket(s); }}}, {OperatorPlusMinus, {S6, [this](string s) {has_plus_minus_operator(s); }}}, {OperatorMultDiv, {S7, [this](string s) {has_mult_div_operator(s); }}}, {Error, {S9, [this](string s) {has_error(s); }}}}},
	{S2, {{Number, {S9,[this](string s) {has_error(s); } }},{BracketOpen, {S9, [this](string s) {has_error(s); }}},{BracketClose, {S2, [this](string s) {has_close_bracket(s); }}}, {OperatorPlusMinus, {S3, [this](string s) {has_plus_minus_operator(s); }}}, {OperatorMultDiv, {S3, [this](string s) {has_mult_div_operator(s); }}}, {Error, {S9, [this](string s) {has_error(s); }}}}},
	{S3, {{Number, {S4,[this](string s) {has_number(s); } }},{BracketOpen, {S0, [this](string s) {has_open_bracket(s); }}},{BracketClose, {S9, [this](string s) {has_error(s); }}}, {OperatorPlusMinus, {S9, [this](string s) {has_error(s); }}}, {OperatorMultDiv, {S9, [this](string s) {has_error(s); }}}, {Error, {S9, [this](string s) {has_error(s); }}}}},
	{S4, {{Number, {S9,[this](string s) {has_error(s); } }},{BracketOpen, {S9, [this](string s) {has_error(s); }}},{BracketClose, {S4, [this](string s) {has_close_bracket(s); }}}, {OperatorPlusMinus, {S5, [this](string s) {has_plus_minus_operator(s); }}}, {OperatorMultDiv, {S5, [this](string s) {has_mult_div_operator(s); }}}, {Error, {S9, [this](string s) {has_error(s); }}}}},
	{S5, {{Number, {S4,[this](string s) {has_number(s); } }},{BracketOpen, {S0, [this](string s) {has_open_bracket(s); }}},{BracketClose, {S9, [this](string s) {has_error(s); }}}, {OperatorPlusMinus, {S9, [this](string s) {has_error(s); }}}, {OperatorMultDiv, {S9, [this](string s) {has_error(s); }}}, {Error, {S9, [this](string s) {has_error(s); }}}}},
	{S6, {{Number, {S4,[this](string s) {has_number(s); } }},{BracketOpen, {S0, [this](string s) {has_open_bracket(s); }}},{BracketClose, {S9, [this](string s) {has_error(s); }}}, {OperatorPlusMinus, {S6, [this](string s) {has_error(s); }}}, {OperatorMultDiv, {S9, [this](string s) {has_error(s); }}}, {Error, {S9, [this](string s) {has_error(s); }}}}},
	{S7, {{Number, {S2,[this](string s) {has_number(s); } }},{BracketOpen, {S0, [this](string s) {has_open_bracket(s); }}},{BracketClose, {S9, [this](string s) {has_error(s); }}}, {OperatorPlusMinus, {S9, [this](string s) {has_error(s); }}}, {OperatorMultDiv, {S9, [this](string s) {has_error(s); }}}, {Error, {S9, [this](string s) {has_error(s); }}}}},
	{S8, {{Number, {S9,[this](string s) {has_error(s); } }},{BracketOpen, {S9, [this](string s) {has_error(s); }}},{BracketClose, {S8, [this](string s) {has_close_bracket(s); }}}, {OperatorPlusMinus, {S3, [this](string s) {has_plus_minus_operator(s); }}}, {OperatorMultDiv, {S3, [this](string s) {has_mult_div_operator(s); }}}, {Error, {S9, [this](string s) {has_error(s); }}}}}
	
	};
}

