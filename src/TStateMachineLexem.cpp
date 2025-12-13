#include "TStateMachineLexem.h"
#include "tqueue.h"
#include <functional>
#include <iostream>


TStateMachineLexem::Signal TStateMachineLexem::getSignal(char s) {
	if (s >= '0' && s <= '9') return Number;
	if (s == '-') return OperatorMinus;
	if (s == '+' || s == '*' || s == '/') return OperatorPlusMultDiv;
	if (s == '(') return BracketOpen;
	if (s == ')') return BracketClose;
	return Error;
}

//void TStateMachineLexem::has_first_number(char c){
//	buffer = c;
//}
//void TStateMachineLexem::has_operator(char c) {
//	output.push(string(1,c));
//}
//void TStateMachineLexem::has_other_number(char c) {
//	buffer += c;
//}
//void TStateMachineLexem::has_number_and_operator(char c) {
//	if (!buffer.empty()) {
//		output.push(buffer);
//		buffer.clear();
//	}
//	output.push(string(1, c));
//}
//void TStateMachineLexem::has_error(char c) {
//	throw runtime_error("Error state");
//}

void TStateMachineLexem::has_number0(char c){
	buffer = c;
}
void TStateMachineLexem::has_number1(char c) {
	buffer += c;
}
void TStateMachineLexem::has_number2(char c) {
	buffer += c;
}
void TStateMachineLexem::has_number3(char c) {
	buffer += c;
}

void TStateMachineLexem::has_operator_minus0(char c) {
	buffer = c;
}
void TStateMachineLexem::has_operator_minus2(char c) {
	output.push(string(1, '0'));
	output.push(string(1, buffer[0]));
	string temp;
	for (int i = 1; i < buffer.length(); i++) {
		temp += buffer[i];
	}
	output.push(temp);
	output.push(string(1, c));
}
void TStateMachineLexem::has_operator_minus3(char c) {
	if (!buffer.empty()) {
		output.push(buffer);
		buffer.clear();
	}
	output.push(string(1, c));
}

void TStateMachineLexem::has_operator_plus_mult_div0(char c) {
	output.push(string(1, c));
}
void TStateMachineLexem::has_operator_plus_mult_div2(char c) {
	output.push(string(1, '0'));
	output.push(string(1, buffer[0]));
	string temp;
	for (int i = 1; i < buffer.length(); i++) {
		temp += buffer[i];
	}
	output.push(temp);
	output.push(string(1, c));
}
void TStateMachineLexem::has_operator_plus_mult_div3(char c) {
	if (!buffer.empty()) {
		output.push(buffer);
		buffer.clear();
	}
	output.push(string(1, c));
}

void TStateMachineLexem::has_bracket_open0(char c) {
	output.push(string(1, c));
}
void TStateMachineLexem::has_bracket_open1(char c) {
	output.push(string(1, '0'));
	output.push(buffer);
	output.push(string(1, c));
}


void TStateMachineLexem::has_bracket_close0(char c) {
	output.push(string(1, c));
}
void TStateMachineLexem::has_bracket_close2(char c) {
	output.push(string(1, '0'));
	output.push(string(1, buffer[0]));
	string temp;
	for (int i = 1; i < buffer.length(); i++) {
		temp += buffer[i];
	}
	output.push(temp);
	output.push(string(1, c));
}
void TStateMachineLexem::has_bracket_close3(char c) {
	output.push(buffer);
	output.push(string(1, c));
}

void TStateMachineLexem::has_error(char c) {
	throw runtime_error("Error state lexem");
}




//TQueue<string> TStateMachineLexem::parseWithFiniteAutomatonOrThrow() {
//	buffer.clear();
//	for (int i = 0; i < this->input.length(); i++) {
//		Signal current_signal = getSignal(input[i]);
//		State new_state = transitionTable[current_state][current_signal].new_state;
//		transition_callback worker = transitionTable[current_state][current_signal].worker;
//		if (worker != NULL) {
//			worker(input[i]);
//		}
//		current_state = new_state;
//	}
//	if (current_state == S1 && !buffer.empty()) {
//		output.push(buffer);
//		buffer.clear();
//	}
//	return this->output;
//}

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
	if (current_state == S2 && !buffer.empty()) {
		output.push(string(1, buffer[0]));
		string temp;
		for (int i = 1; i < buffer.length(); i++) {
			temp += buffer[i];
		}
		output.push(temp);
		buffer.clear();
	}
	if (current_state == S3 && !buffer.empty()) {
		output.push(buffer);
		buffer.clear();
	}
	/*TQueue<string> output_for_print = output;
	while (!output_for_print.isEmpty()) {
		std::cout << output_for_print.pop()<<" ";
	}*/
	return this->output;
}



//TStateMachineLexem::TStateMachineLexem(const string& _input) :input(_input), current_state(S0) {
//	transitionTable = {
//	{S0, {{Number, {S1,[this](char c) {has_first_number(c); } }},{OperatorBracket, {S0, [this](char c) {has_operator(c); }}},{Error, {S2, [this](char c) {has_error(c); } }}}},
//	{S1, {{Number, {S1, [this](char c) {has_other_number(c); } }},{OperatorBracket, {S0, [this](char c) {has_number_and_operator(c); }}},{Error, {S2, [this](char c) {has_error(c); }}}}}
//	};
//}

TStateMachineLexem::TStateMachineLexem(const string& _input) :input(_input), current_state(S0) {
	transitionTable = {
	{S0, {{Number, {S3,[this](char c) {has_number0(c); } }},{OperatorMinus, {S1, [this](char c) {has_operator_minus0(c); }}},{OperatorPlusMultDiv, {S0, [this](char c) {has_operator_plus_mult_div0(c); }}},{BracketOpen, {S0, [this](char c) {has_bracket_open0(c); }}},{BracketClose, {S0, [this](char c) {has_bracket_close0(c); }}}, {Error, {S4, [this](char c) {has_error(c); } }}}},
	{S1, {{Number, {S2,[this](char c) {has_number1(c); } }},{OperatorMinus, {S4, [this](char c) {has_error(c); }}},{OperatorPlusMultDiv, {S4, [this](char c) {has_error(c); }}},{BracketOpen, {S0, [this](char c) {has_bracket_open1(c); }}},{BracketClose, {S4, [this](char c) {has_error(c); }}}, {Error, {S4, [this](char c) {has_error(c); } }}}},
	{S2, {{Number, {S2,[this](char c) {has_number2(c); } }},{OperatorMinus, {S0, [this](char c) {has_operator_minus2(c); }}},{OperatorPlusMultDiv, {S0, [this](char c) {has_operator_plus_mult_div2(c); }}},{BracketOpen, {S4, [this](char c) {has_error(c); }}},{BracketClose, {S0, [this](char c) {has_bracket_close2(c); }}}, {Error, {S4, [this](char c) {has_error(c); } }}}},
	{S3, {{Number, {S3,[this](char c) {has_number3(c); } }},{OperatorMinus, {S0, [this](char c) {has_operator_minus3(c); }}},{OperatorPlusMultDiv, {S0, [this](char c) {has_operator_plus_mult_div3(c); }}},{BracketOpen, {S4, [this](char c) {has_error(c); }}},{BracketClose, {S0, [this](char c) {has_bracket_close3(c); }}}, {Error, {S4, [this](char c) {has_error(c); } }}}}
	
	};
}

