#include "calc.h"

pVar initVar(const char *name = NULL, vType format = -1, int32_t iVal = 0, float fVal = 0) {
    pVar var = (pVar)malloc(sizeof(sVar));
    var->name = NULL;
    var->format = -1;
    var->iVal = 0;
    var->fVal = 0;
    var->Next = NULL;
    var->Prev = NULL;
    return var;
}

pOpr initOpr() {
    pOpr opr = (pOpr)malloc(sizeof(sOpr));
    opr->type = -1;
    opr->format = -1;
    opr->iVal = 0;
    opr->fVal = 0;
    opr->Next = NULL;
    opr->Prev = NULL;
    return opr;
}

pVar addNextVar(pVar var) {
    if (var->Next == NULL) {
        var->Next = initVar();
        var->Next->Prev = var;
    }
    return var->Next;
}

pOpr addNextOpr(pOpr opr) {
    if (opr->Next == NULL) {
        opr->Next = initOpr();
        opr->Next->Prev = opr;
    }
    return opr->Next;
}

pVar insertVar(pVar var, char *name, vType format) {
    pVar newVar = initVar();
    newVar->name = name;
    newVar->format = format;

    if (var == NULL) return newVar;
    newVar->Prev = var;
    newVar->Next = var->Next;
    var->Next = newVar;

    if (newVar->Next == NULL) return newVar;
    newVar->Next->Prev = newVar;
    return newVar;
}

pOpr insertOpr(pOpr opr, opType type, vType format) {
    pOpr newOpr = initOpr();
    newOpr->type = type;
    newOpr->format = format;

    if (opr == NULL) return newOpr;
    newOpr->Prev = opr;
    newOpr->Next = opr->Next;
    opr->Next = newOpr;

    if (newOpr->Next == NULL) return newOpr;
    newOpr->Next->Prev = newOpr;
    return newOpr;
}

void freeVar(pVar var) {
    if (var == NULL) return;
    freeVar(var->Next);
    free(var->name);
    free(var);
    var = NULL;
    return;
}

void freeOpr(pOpr opr) {
    if (opr == NULL) return;
    freeOpr(opr->Next);
    free(opr);
    opr = NULL;
    return;
}
