#pragma once
#include "tqueue.h"
#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <functional>

using namespace std;


class TStateMachineLexem {
    string input;
    /*enum State {
        S0,
        S1,
        S2
    };*/
    enum State {
        S0,
        S1,
        S2,
        S3,
        S4
    };
    /*enum Signal {
        Number,
        OperatorBracket,
        Error
    };*/
    enum Signal {
        Number,
        OperatorMinus,
        OperatorPlusMultDiv,
        BracketOpen,
        BracketClose,
        Error
    };
    enum State current_state;
    /*typedef void (*transition_callback)(int i);*/
    using transition_callback = function<void(char)>;
    struct transition
    {
        State new_state;
        transition_callback worker;
    };
    //transition FSM_table[3][3];
    
    TQueue<string> output;
    string buffer;
    int znak;

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
    TQueue<string> parseWithFiniteAutomatonOrThrow();

    TStateMachineLexem(const string& _input);


    Signal getSignal(char s);
    /*void has_first_number(char c);
    void has_operator(char c);
    void has_error(char c);
    void has_other_number(char c);
    void has_number_and_operator(char c);*/
    void has_number0(char c);
    void has_number1(char c);
    void has_number2(char c);
    void has_number3(char c);
    void has_operator_minus0(char c);
    void has_operator_minus1(char c);
    void has_operator_minus2(char c);
    void has_operator_minus3(char c);
    void has_operator_plus_mult_div0(char c);
    void has_operator_plus_mult_div1(char c);
    void has_operator_plus_mult_div2(char c);
    void has_operator_plus_mult_div3(char c);
    void has_bracket_open0(char c);
    void has_bracket_open1(char c);
    void has_bracket_open2(char c);
    void has_bracket_open3(char c);
    void has_bracket_close0(char c);
    void has_bracket_close1(char c);
    void has_bracket_close2(char c);
    void has_bracket_close3(char c);
    void has_error(char c);
};
