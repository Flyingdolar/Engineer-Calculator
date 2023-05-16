#include <getopt.h>
#include <string.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "calc.h"
#include "macros.h"

using namespace std;

const char *shortOpt = "i:o:hd";
const option longOpt[] = {
    {"input", required_argument, nullptr, 'i'},
    {"output", required_argument, nullptr, 'o'},
    {"help", no_argument, nullptr, 'h'},
    {nullptr, 0, nullptr, 0}};

void printHelp() {
    PRINT("This is a Engineering Calculator.");
    PRINT("Parameters & Usages:");
    PRINT("-d --direct             Run this program directly without any input or output file");
    PRINT("-i, --input <File Name>   Specific input file name");
    PRINT("-o, --output <File Name>  Specific output file name");
    PRINT("-h, --help               Show this help message");
    return;
}

int checkCmd(bool cmd[], string inFile, string outFile) {
    if (cmd[0] && inFile.empty()) {
        PRINTERR("No input file specified.");
        PRINTHINT("File name should be defined after \"-i\".");
        return -1;
    }

    if (cmd[1] && outFile.empty()) {
        PRINTERR("No output file specified.");
        PRINTHINT("File name should be defined after \"-o\".");
        return -1;
    }

    if ((cmd[0] && !cmd[1]) || (!cmd[0] && cmd[1])) {
        PRINTERR("Input and output file should be specified at the same time.");
        PRINTHINT("Parameter \"-i\" and \"-o\" should be used together.");
        return -1;
    }

    if (!(cmd[0] || cmd[1] || cmd[3])) {
        PRINTERR("No function specified.");
        PRINTHINT("Please use \"-i\" and \"-o\" to specify input and output file.");
        PRINTHINT("Or use \"-d\" to do operate directly.");
        return -1;
    }

    return 0;
}

int readFile(string fileName, vector<string> &strVar, vector<string> &strOpr) {
    ifstream FIN(fileName);
    string line;

    if (!FIN.is_open()) {
        PRINTERR("Failed to open input file.");
        PRINTHINT("File name: " + fileName << "cannot be opened.");
        PRINTHINT("Please check if the file exists.");
        PRINTHINT("Also check if you have the permission to read it.");
        return -1;
    }

    while (getline(FIN, line)) {
        if (line.empty()) continue;

        if (line.find('=') != string::npos)
            strOpr.emplace_back(line);
        else
            strVar.emplace_back(line);
    }

    FIN.close();
    return 0;
}

int writeFile(string fileName, vector<Variable> varList) {
    ofstream FOUT(fileName);

    if (!FOUT.is_open()) {
        PRINTERR("Failed to open output file.");
        PRINTHINT("File name: " + fileName << "cannot be opened.");
        PRINTHINT("Please check if the file exists.");
        PRINTHINT("Also check if you have the permission to write it.");
        return -1;
    }

    for (auto var : varList) {
        FOUT << var.name << " = ";
        if (var.value.index() == 0)
            FOUT << get<int>(var.value);
        else
            FOUT << get<float>(var.value);
        FOUT << endl;
    }

    FOUT.close();
    return 0;
}

int main(int argc, char *argv[]) {
    int option;
    bool cmd[4] = {false};
    string inFile, outFile, stdInput;
    vector<string> strVar, strOpr;
    vector<Variable> varList;

    // Parse Command Line Arguments
    while ((option = getopt_long(argc, argv, shortOpt, longOpt, nullptr)) != -1) {
        if (option == 'i') cmd[0] = true, inFile = optarg;
        if (option == 'o') cmd[1] = true, outFile = optarg;
        if (option == 'h') cmd[2] = true, printHelp();
        if (option == 'd') cmd[3] = true;
    }

    // Check Command Line Arguments
    if (cmd[2]) return 0;
    if (checkCmd(cmd, inFile, outFile) == -1) return -1;

    if (cmd[0] && cmd[1]) {
        // Open Input File
        if (readFile(inFile, strVar, strOpr) == -1) return -1;
        // Set Variables and Calculate
        if (setVariable(strVar, varList) == -1) return -1;
        if (calculate(strOpr, varList) == -1) return -1;
        // Write Output File
        if (writeFile(outFile, varList) == -1) return -1;
        cout << "Result has been written to file: " << outFile << endl;
    }
    if (cmd[3]) {
        PRINT("Please input the expression you want to calculate.");
        cout << ">>> ";
        getline(cin, stdInput), strOpr.push_back(stdInput);
        cout << "Result: ";
        if (calculate(strOpr, varList) == -1) return -1;
    }

    return 0;
}
