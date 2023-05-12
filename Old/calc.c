#include "calc.h"

void parseVar(const char *varStr, char option) {
    return;
}

pOpr parseOpr(const char *oprStr) {
    bool flag;
    char *str = (char *)oprStr;
    float dec;
    pVar varPtr;
    pOpr oprHead, opr;

    if (oprStr == NULL) return NULL;
    while (*str != 0 && *str != '\n') {
        flag = 0;
        // Handle Space
        if (*str == ' ') {
            str++;
            continue;
        }
        // Handle Operand
        if (isdigit(*str) >= 0) {
            opr = insertOpr(opr, OPRAND, VINT);
            while (isdigit(*str)) {
                opr->iVal = opr->iVal * 10 + (*str - '0');
                str++;
            }
            if (*str == '.') {
                opr->format = VFLOAT;
                opr->fVal = opr->iVal;
                dec = 0.1, str++;
                while (isdigit(*str)) {
                    opr->fVal += (*str - '0') * dec;
                    dec /= 10, str++;
                }
            }
            continue;
        }
        // Handle Operator
        for (size_t idx = 0; opStr[idx] != NULL; idx++) {
            if (strncmp(str, opStr[idx], strlen(opStr[idx])) == 0) {
                opr = insertOpr(opr, (opType)idx, -1);
                str += strlen(opStr[idx]), flag = 1;
                break;
            }
        }
        if (flag) continue;
        // Handle Variable
        varPtr = varHead;
        while (varPtr != NULL) {
            if (strncmp(str, varPtr->name, strlen(varPtr->name)) == 0) {
                opr = insertOpr(opr, OPRAND, varPtr->format);
                if (opr->format == VINT) opr->iVal = varPtr->iVal;
                if (opr->format == VFLOAT) opr->fVal = varPtr->fVal;
                str += strlen(varPtr->name), flag = 1;
                break;
            }
            varPtr = varPtr->Next;
        }
        if (flag) continue;
        // None of All
        return NULL;
    }
    oprHead = opr;
    while (oprHead->Prev != NULL) oprHead = oprHead->Prev;
    return oprHead;
}

int32_t calcOpr(pOpr oprHead) {
    int ans = 0;
    return ans;
}

int32_t Calculate(FILE *fp) {
    char data[1000];
    pVar varPtr;
    pOpr oprList;
    size_t len;

    if (fp == NULL) return 0;
    while (fgets(data, 1000, fp) != NULL) {
        if (strncmp(data, "int", 3) == 0) {
            if (parseVar(data, 'i') == -1) return -1;
            continue;
        }
        if (strncmp(data, "float", 5) == 0) {
            if (parseVar(data, 'f') == -1) return -2;
            continue;
        }
        if (varHead != NULL) {
            varPtr = varHead;
            while (varPtr != NULL) {
                len = strlen(varPtr->name);
                if (strncmp(data, varPtr->name, len) == 0)
                    break;
                varPtr = varPtr->Next;
            }
            if (varPtr != NULL) {
                oprList = (pOpr)malloc(sizeof(sOpr));
                oprList->Prev = NULL;
                oprList->Next = NULL;
                if (parseOpr(data + len, oprList) == -1) return -3;
                if (calcOpr(oprList) == -1) return -4;
                if (varPtr->format == VINT) {
                    varPtr->iVal = oprList->iVal;
                } else {
                    varPtr->fVal = oprList->fVal;
                }
                freeOpr(oprList);
            }
        }
    }
    return 0;
}
