#pragma once
#include <iostream>
#include <string>
#include <variant>
#include <vector>

using namespace std;

struct Variable {
    string name;
    variant<int, float> value;
};

int setVariable(vector<string> strList, vector<Variable>& varList);
int calculate(vector<string> strList, vector<Variable>& varList);
