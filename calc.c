#include "calc.h"

pOpr nextNode(pOpr opr) {
    if (opr->next == NULL) {
        opr->next = (pOpr)malloc(sizeof(sOpr));
        opr->next->prev = opr;
    }
    return opr->next;
}

int32_t parseOpr(const char *oprStr, pOpr oprHead) {
    pOpr opr = oprHead;
    char *str = oprStr;
    int degree, flag;
    float dec;

    if (oprHead == NULL) return -1;
    if (oprStr == NULL) return 0;

    while (*str != 0) {
        // Handle Space
        if (*str == ' ') {
            str++;
            continue;
        }
        // Handle Operand
        if (isdigit(*str) >= 0) {
            opr = nextNode(opr);
            opr->type = OPRAND;
            opr->format = VINT;
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
        flag = 0;
        for (int idx = 0; idx < (sizeof(opStr) / sizeof(char *)); idx++) {
            if (strncmp(str, opStr[idx], strlen(opStr[idx])) == 0) {
                opr = nextNode(opr);
                opr->type = idx;
                str += strlen(opStr[idx]);
                flag = 1;
                break;
            }
        }
        if (flag) continue;
        // Handle Variable

        // None of All
        return -1;
    }

    return 0;
}

int calc(FILE *fp) {
    char data[1000];

    if (fp == NULL) return 0;
    while (fgets(data, 1000, fp) != NULL) {
    }
    return 0;
}
