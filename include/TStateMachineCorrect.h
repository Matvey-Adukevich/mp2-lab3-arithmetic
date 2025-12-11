#pragma once
#include "tqueue.h"
#include "tstack.h"
#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <functional>

using namespace std;


class TStateMachineCorrect {
    TQueue<string> input;
    enum State {
        S0,
        S1,
        S2,
        S3,
        S4,
        S5,
        S6,
        S7,
        S8,
        S9
    };
    enum Signal {
        Number,
        OperatorPlusMinus,
        OperatorMultDiv,
        BracketOpen,
        BracketClose,
        Error
    };
    enum State current_state;
    /*typedef void (*transition_callback)(int i);*/
    using transition_callback = function<void(string)>;
    struct transition
    {
        State new_state;
        transition_callback worker;
    };
    //transition FSM_table[3][3];

    /*TQueue<string> output;*/
    bool output;
    TQueue<string> buffer;
    TStack<string> stack;

    map<State, map<Signal, transition>> transitionTable;//{
    //    {S0, {{Number, {S1,[this](char c){has_first_number(c); } }},{OperatorBracket, {S0, has_operator}},{Error, {S2, has_error}}} },
    //    {S1, {{Number, {S1, has_other_number}},{OperatorBracket, {S0, has_number_and_operator}},{Error, {S2, has_error}}}}
    //};

    // Исключение для строк, не принадлежащих языку
    struct LanguageException : public runtime_error {
        explicit LanguageException(const string& msg) : runtime_error(msg) {}
    };


    //// Состояния конечного автомата
    //enum State {
    //    S0,
    //    S1
    //};


    //// Таблица переходов: [состояние][символ] -> новое состояние
    //map<State, map<char, State>> transitionTable = {
    //    {S0, {{'a', S1}}},
    //    {S1, {{'b', S2}, {'d', S2}}},
    //    {S2, {{'c', S3}}}
    //};


    //// Таблица событий: [состояние][символ] -> распознанное слово (если есть)
    //map<State, map<char, string>> eventTable = {
    //    {S1, {{'d', "ad"}}},     // Переход S1 --d--> S2: слово "ad" завершено
    //    {S2, {{'c', "abc"}}}     // Переход S2 --c--> S3: слово "abc" завершено
    //};

public:
    // Основная функция: проверяет, принадлежит ли строка языку
    bool parseWithFiniteAutomatonOrThrow();

    TStateMachineCorrect(const TQueue<string>& _input);


    Signal getSignal(string s);
    void has_error(string s);
    void has_number(string s);
    void has_open_bracket(string s);
    void has_close_bracket(string s);
    void has_plus_minus_operator(string s);
    void has_mult_div_operator(string s);
    //void has_first_number(char c);
    //void has_operator(char c);
    //void has_error(char c);
    //void has_other_number(char c);
    //void has_number_and_operator(char c);


};
