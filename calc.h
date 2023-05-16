#pragma once
#include <math.h>

#include <iostream>
#include <regex>
#include <string>
#include <variant>
#include <vector>

using namespace std;

enum Operator {
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    MOD,
    EXP,
    LOG,
    SQRT,
    SIN,
    COS,
    TAN,
    LBR,
    RBR,
    LSP,
    RSP,
    EQU
};

enum Constant {
    PI,
    NATURE
};

const pair<string, int> opStr[] = {
    {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}, {"mod", 3}, {"exp", 3}, {"log", 3}, {"sqrt", 3}, {"sin", 3}, {"cos", 3}, {"tan", 3}, {"(", 0}, {")", 0}, {"[", 0}, {"]", 0}, {"=", 0}};

const pair<string, float> constStr[] = {
    {"PI", acos(-1)}, {"E", 2.7182818284590452353602874713527f}};

struct Variable {
    string name;
    variant<int, float> value;
};

struct OpElement {
    enum class Type {
        EMPTY,
        OPERATOR,
        VARIABLE,
        INT,
        FLOAT
    };
    Type type;
    int getNum;
    variant<Operator, int, float> value;
};

// Parser.cpp: Parser functions
int setVariable(vector<string> strList, vector<Variable> &varList);
int setOperation(string str, int &resVar, vector<OpElement> &opList, vector<Variable> &varList);

// Calc.cpp: Calculator functions
int calculate(vector<string> strList, vector<Variable> &varList);
