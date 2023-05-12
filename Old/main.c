#include <stdio.h>

#include "calc.h"

int printErr(const char *msg) {
    printf("\033[1;31mE:%s\n\033[0m", msg);
    return -1;
}

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
    if (parseOpr(data, oprHead) == -1) printErr("Parse error");
    // if (calc(fp) == -1) printErr("Calc error");
    fclose(fp);
    return 0;
}
