#include "calc.h"

#include <regex>
#include <string>
#include <vector>

#include "macros.h"

using namespace std;

regex pattern(R"(-?\d+(\.\d+)?|[a-z]+|[=\+\-\*\/\(\)])");
regex comment(R"(\/\/.*)");
regex digit(R"(-?\d+(\.\d+)?)");

int setVariable(vector<string> strList, vector<Variable> &varList) {
    Variable var = {"", 0};
    for (auto &str : strList) {
        str = regex_replace(str, comment, "");
        sregex_iterator it(str.begin(), str.end(), pattern), end_it;
        for (; it != end_it; ++it) {
            if (it->str() == "int" || it->str() == "float") {
                if (it->str() == "int") var.value = 0;
                if (it->str() == "float") var.value = 0.0f;
                continue;
            }
            var.name = it->str();
            varList.push_back(var);
        }
    }
    return 0;
}

int parseElement(string str, Variable resVar, vector<OpElement> &opList, vector<Variable> &varList) {
    sregex_iterator it(str.begin(), str.end(), pattern), end_it;
    for (auto var : varList) {
        if (var.name.compare(it->str()) == 0) {
            resVar = var;
            break;
        }
    }
    if (resVar.name.empty()) {
        PRINTERR("Variable \"" + it->str() + "\" not found.");
        PRINTHINT("Please check if you have defined it.");
        return -1;
    }
    ++it;
    // 原本的: if (it->str() != "=")
    if (it->str().compare("=") != 0) {
        PRINTERR("Invalid expression.");
        PRINTHINT("Please check if you have missed \"=\".");
        return -1;
    }
    ++it;
    for (; it != end_it; ++it) {
        OpElement op;
        // Find if it is an operator (Match the string in opStr)
        for (size_t idx = 0; idx < sizeof(opStr) / sizeof(opStr[0]); ++idx) {
            if (it->str().compare(opStr[idx].first) == 0) {
                op.type = OpElement::Type::OPERATOR;
                op.value = static_cast<Operator>(idx);
                opList.push_back(op);
                break;
            }
        }
        if (op.type == OpElement::Type::OPERATOR) return 0;

        // Find if it is a constant (Match the string in constStr)
        for (size_t idx = 0; idx < sizeof(constStr) / sizeof(constStr[0]); ++idx) {
            if (it->str().compare(constStr[idx].first) == 0) {
                op.type = OpElement::Type::FLOAT;
                op.value = constStr[idx].second;
                opList.push_back(op);
                break;
            }
        }
        if (op.type == OpElement::Type::FLOAT) return 0;

        // Find if it is a variable (Match the string in varList)
        for (auto var : varList) {
            if (it->str().compare(var.name) == 0) {
                op.type = OpElement::Type::VARIABLE;
                op.value = var;
                opList.push_back(op);
                break;
            }
        }
        if (op.type == OpElement::Type::VARIABLE) return 0;

        // Find if it is a number (Match the string in regex)
        if (regex_match(it->str(), digit)) {
            if (it->str().find('.') == string::npos) {
                op.type = OpElement::Type::INT;
                op.value = stoi(it->str());
            } else {
                op.type = OpElement::Type::FLOAT;
                op.value = stof(it->str());
            }
            opList.push_back(op);
            return 0;
        }

        // Find if it is a semi-colon, End Process
        if (it->str().compare(";") == 0) return 0;

        // If it is not any of the above, then it is an error
        PRINTERR("Invalid expression \"" << it->str() << "\" found.");
        PRINTHINT("Please check if you have defined it.");
        return -1;
    }
    return 0;
}

int calculate(vector<string> strList, vector<Variable> &varList) {
    for (auto &str : strList) {
        Variable resVar;
        vector<OpElement> opList;
        if (parseElement(str, resVar, opList, varList) == -1) return -1;
        // Debug: Print the opList
        for (auto op : opList) {
            switch (op.type) {
                case OpElement::Type::INT:
                    cout << get<int>(op.value) << " ";
                    break;
                case OpElement::Type::FLOAT:
                    cout << get<float>(op.value) << " ";
                    break;
                case OpElement::Type::VARIABLE:
                    cout << get<Variable>(op.value).name << " ";
                    break;
                case OpElement::Type::OPERATOR:
                    int num = (int)get<Operator>(op.value);
                    cout << opStr[num].first << " ";
                    break;
            }
        }
    }
    return 0;
}
