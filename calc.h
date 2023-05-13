#pragma once
#include <math.h>

#include <iostream>
#include <string>
#include <variant>
#include <vector>

using namespace std;

enum class Operator {
    ADD,
    SUB,
    MUL,
    DIV,
    EXP,
    LOG,
    SQRT,
    SIN,
    COS,
    TAN,
    LBR,
    RBR,
    LSP,
    RSP
};

enum class Constant {
    PI,
    E
};

const pair<string, int> opStr[] = {
    {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}, {"log", 3}, {"sqrt", 3}, {"sin", 3}, {"cos", 3}, {"tan", 3}, {"(", 0}, {")", 0}, {"[", 0}, {"]", 0}};

const pair<string, float> constStr[] = {
    {"pi", 3.1415926535897932384626433832795f}, {"e", 2.7182818284590452353602874713527f}};

struct Variable {
    string name;
    variant<int, float> value;
};

struct OpElement {
    enum class Type {
        OPERATOR,
        VARIABLE,
        INT,
        FLOAT
    };
    Type type;
    variant<Operator, Variable, int, float> value;
};

int setVariable(vector<string> strList, vector<Variable>& varList);
int calculate(vector<string> strList, vector<Variable>& varList);
