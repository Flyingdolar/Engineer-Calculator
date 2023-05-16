#include "calc.h"

#include <regex>
#include <string>
#include <vector>

#include "macros.h"

using namespace std;

int setPosix(vector<OpElement> &opList, vector<Variable> &varList) {
    vector<OpElement> todo = move(opList), stack;

    while (!(todo.empty())) {
        if (todo.begin()->type == OpElement::Type::OPERATOR) {
            if (get<int>(todo.begin()->value) == Operator::LBR) {
                stack.push_back(todo.front());
                todo.erase(todo.begin());
            } else if (get<int>(todo.begin()->value) == Operator::RBR) {
                while (get<int>(stack.back().value) != Operator::LBR) {
                    opList.push_back(stack.back());
                    stack.pop_back();
                }
                stack.pop_back();
                todo.erase(todo.begin());
            } else if (get<int>(todo.begin()->value) == Operator::LSP) {
                stack.back().getNum = 2;
                stack.push_back(todo.front());
                todo.erase(todo.begin());
            } else if (get<int>(todo.begin()->value) == Operator::RSP) {
                while (get<int>(stack.back().value) != Operator::LSP) {
                    opList.push_back(stack.back());
                    stack.pop_back();
                }
                stack.pop_back();
                todo.erase(todo.begin());
            } else {
                if (!(stack.empty())) {
                    while (!(stack.empty()) && opStr[get<int>(stack.back().value)].second >= opStr[get<int>(todo.front().value)].second) {
                        opList.push_back(stack.back());
                        stack.pop_back();
                    }
                }
                stack.push_back(todo.front());
                todo.erase(todo.begin());
            }
        } else if (todo.begin()->type == OpElement::Type::VARIABLE) {
            todo.begin()->type = OpElement::Type::FLOAT;
            if (varList[get<int>(todo.begin()->value)].value.index() == 0) {
                todo.begin()->value = static_cast<float>(get<int>(varList[get<int>(todo.begin()->value)].value));
            } else if (varList[get<int>(todo.begin()->value)].value.index() == 1) {
                todo.begin()->value = get<float>(varList[get<int>(todo.begin()->value)].value);
            }
            opList.push_back(todo.front());
            todo.erase(todo.begin());
        } else {
            opList.push_back(todo.front());
            todo.erase(todo.begin());
        }
    }
    while (!(stack.empty())) {
        opList.push_back(stack.back());
        stack.pop_back();
    }
    return 0;
}

int calculate(vector<string> strList, vector<Variable> &varList) {
    for (auto &str : strList) {
        int resVar = -1;
        vector<OpElement> opList, opStack;

        if (setOperation(str, resVar, opList, varList) == -1) return -1;
        if (setPosix(opList, varList) == -1) return -1;

        while (!(opList.empty())) {
            if (opList.begin()->type == OpElement::Type::OPERATOR) {
                auto val1 = opStack.back(), val2 = opStack.back();
                if (opList.front().getNum == 2) {
                    val2 = opStack[opStack.size() - 2];
                    opStack.pop_back();
                }
                opStack.pop_back();
                switch (get<int>(opList.front().value)) {
                    case Operator::ADD:
                        val1.value = get<float>(val1.value) + get<float>(val2.value);
                        break;
                    case Operator::SUB:
                        val1.value = get<float>(val2.value) - get<float>(val1.value);
                        break;
                    case Operator::MUL:
                        val1.value = get<float>(val1.value) * get<float>(val2.value);
                        break;
                    case Operator::DIV:
                        val1.value = get<float>(val2.value) / get<float>(val1.value);
                        break;
                    case Operator::MOD:
                        val1.value = (int)get<float>(val2.value) % (int)get<float>(val1.value);
                        break;
                    case Operator::POW:
                        val1.value = pow(get<float>(val2.value), get<float>(val1.value));
                        break;
                    case Operator::EXP:
                        val1.value = exp(get<float>(val1.value));
                        break;
                    case Operator::LOG:
                        val1.value = log(get<float>(val1.value)) / log(static_cast<float>(10));
                        if (opList.front().getNum == 2) {
                            val2.value = log(get<float>(val2.value));
                            val1.value = get<float>(val2.value) / get<float>(val1.value);
                        }
                        break;
                    case Operator::SIN:
                        val1.value = sin(get<float>(val1.value));
                        if (opList.front().getNum == 2 && get<int>(val2.value) == -1)
                            val1.value = asin(get<float>(val1.value));
                        break;
                    case Operator::COS:
                        val1.value = cos(get<float>(val1.value));
                        if (opList.front().getNum == 2 && get<int>(val2.value) == -1)
                            val1.value = acos(get<float>(val1.value));
                        break;
                    case Operator::TAN:
                        val1.value = tan(get<float>(val1.value));
                        if (opList.front().getNum == 2 && get<int>(val2.value) == -1)
                            val1.value = atan(get<float>(val1.value));
                        break;
                    case Operator::SQRT:
                        val1.value = sqrt(get<float>(val1.value));
                        if (opList.front().getNum == 2)
                            val1.value = pow(get<float>(val1.value), 1 / get<float>(val2.value));
                        break;
                }
                opStack.push_back(val1);
                opList.erase(opList.begin());
            } else {
                opStack.push_back(opList.front());
                opList.erase(opList.begin());
            }
        }

        if (resVar >= 0) {
            if (opStack.back().type == OpElement::Type::INT) {
                varList[resVar].value = static_cast<int>(get<int>(opStack.back().value));
            } else if (opStack.back().type == OpElement::Type::FLOAT) {
                varList[resVar].value = get<float>(opStack.back().value);
            }
        } else {
            cout << get<float>(opStack.back().value) << endl;
        }
    }

    return 0;
}
