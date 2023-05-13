#include "calc.h"

#include <regex>
#include <string>
#include <vector>

#include "macros.h"

using namespace std;

regex pattern("/-?\\d+(\\.\\d+)?|[a-z]+|[=\\+\\-\\*\\/\\(\\)]/gm");
regex comment("\\/\\/.*");

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

int calculate(vector<string> strList, vector<Variable> &varList) {
    return 0;
}
