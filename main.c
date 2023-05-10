#include <stdio.h>

#include "calc.h"
#include "tool.h"

int main() {
    char filename[100];
    char data[100];
    pOpr oprHead = (pOpr)malloc(sizeof(sOpr));

    printf("This is a calculator\n");
    printf("Please enter the file name: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return printErr("File not found");

    fgets(data, 100, fp);
    PRINTD(data);
    if (parseOpr(data, oprHead) == -1) printErr("Parse error");
    // if (calc(fp) == -1) printErr("Calc error");
    fclose(fp);
    return 0;
}
