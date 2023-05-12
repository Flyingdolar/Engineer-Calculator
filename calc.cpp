#include "calc.h"

#include <regex>
#include <string>
#include <vector>

#include "macros.h"

using namespace std;

regex pattern("/-?\\d+(\\.\\d+)?|[a-z]+|[=\\+\\-\\*\\/\\(\\)]/gm");
regex comment("\\/\\*.*\\*\\/|\\/\\/.*");

int rmComment(string &str) {
    string::size_type start, end;
    start = str.find("//");
    if (start != string::npos)
        str.erase(start);
    return 0;
}

int setVariable(vector<string> strList, vector<Variable> &varList) {
    string::size_type start, end;

    for (auto &str : strList) {
        rmComment(str);
        if (str.empty()) continue;
        vector<string> wordList;
    }
    return 0;
}

int calculate(vector<string> strList, vector<Variable> &varList) {
    return 0;
}
