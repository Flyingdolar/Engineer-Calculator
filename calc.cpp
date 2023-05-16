#include "calc.h"

#include <regex>
#include <string>
#include <vector>

#include "macros.h"

using namespace std;

int setPosix(vector<OpElement> &opList, vector<Variable> &varList) {
    return 0;
}

int calculate(vector<string> strList, vector<Variable> &varList) {
    for (auto &str : strList) {
        int resVar = -1;
        vector<OpElement> opList;

        if (setOperation(str, resVar, opList, varList) == -1) return -1;
        if (setPosix(opList, varList) == -1) return -1;

        // for (auto op : opList) {
        //     switch (op.type) {
        //         case OpElement::Type::OPERATOR:
        //             cout << "\\" << opStr[get<int>(op.value)].first;
        //             break;
        //         case OpElement::Type::VARIABLE:
        //             cout << "\\" << varList[get<int>(op.value)].name;
        //             break;
        //         case OpElement::Type::INT:
        //             cout << "\\" << get<int>(op.value);
        //             break;
        //         case OpElement::Type::FLOAT:
        //             cout << "\\" << get<float>(op.value);
        //             break;
        //         default:
        //             break;
        //     }
        // }
        // if (resVar >= 0) cout << " = " << varList[resVar].name << endl;
    }

    return 0;
}
