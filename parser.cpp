#include "calc.h"
#include "macros.h"

using namespace std;

// Regex Patterns
regex pattern(R"(-?\d+(\.\d+)?|[a-z]+|[=\+\-\*\/\(\)])");
regex comment(R"(\/\/.*)");
regex digit(R"(-?\d+(\.\d+)?)");

// Parsing & Store Variables
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

// Parsing & Store Expression
int setOperation(string str, int &resVar, vector<OpElement> &opList, vector<Variable> &varList) {
    sregex_iterator it(str.begin(), str.end(), pattern), end_it;
    int index;

    for (; it != end_it; ++it) {
        OpElement element;
        element.type = OpElement::Type::EMPTY;
        // Find if it is an operator (Match the string in opStr)
        index = 0;
        for (auto op : opStr) {
            if (it->str().compare(op.first) == 0) {
                element.type = OpElement::Type::OPERATOR;
                element.value = index;
                opList.push_back(element);
                break;
            }
            ++index;
        }
        // Find if it is a constant (Match the string in constStr)
        if (element.type != OpElement::Type::EMPTY) continue;
        for (auto token : constStr) {
            if (it->str().compare(token.first) == 0) {
                element.type = OpElement::Type::FLOAT;
                element.value = token.second;
                opList.push_back(element);
                break;
            }
        }

        index = 0;
        // Find if it is a variable (Match the string in varList)
        if (element.type != OpElement::Type::EMPTY) continue;
        for (auto var : varList) {
            if (it->str().compare(var.name) == 0) {
                element.type = OpElement::Type::VARIABLE;
                element.value = index;
                opList.push_back(element);
                break;
            }
            ++index;
        }

        // Find if it is a number (Match the string in regex)
        if (element.type != OpElement::Type::EMPTY) continue;
        if (regex_match(it->str(), digit)) {
            if (it->str().find('.') == string::npos) {
                element.type = OpElement::Type::INT;
                element.value = stoi(it->str());
            } else {
                element.type = OpElement::Type::FLOAT;
                element.value = stof(it->str());
            }
            opList.push_back(element);
            continue;
        }

        // If it is not any of the above, then it is an error
        PRINTERR("Invalid expression \"" << it->str() << "\" found.");
        PRINTHINT("Please check if you have defined it.");
        return -1;
    }
    // Type of opList: vector<OpElement> &opList
    if (get<int>(opList[1].value) == 14) {
        resVar = get<int>(opList[0].value);
        opList.erase(opList.begin(), opList.begin() + 2);
    }
    return 0;
}
