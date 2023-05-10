#pragma once
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum _vType_ {
    VINT,
    VFLOAT
} vType;

typedef enum _opType_ {
    OPRAND,
    ADD,
    SUB,
    MULT,
    DIV,
    POW,
    SQRT,
    LOG,
    LOGN,
    SIN,
    COS,
    TAN,
    EXC,
    SEC,
    CSC,
    COT,
    LBR,
    RBR
} opType;

const char *opStr[17] = {
    "+", "-", "*", "/", "^", "sqrt", "log", "logn", "sin", "cos", "tan", "!", "sec", "csc", "cot", "(", ")"};

typedef struct _opr_ *pOpr;
typedef struct _opr_ {
    opType type;   // Type of Operator (or Operand)
    vType format;  // Format of Operand (INT or FLOAT)
    int32_t iVal;  // Integer Value
    float fVal;    // Float Value
    pOpr next;     // Next Operator
    pOpr prev;     // Previous Operator
} sOpr;

// Turn a string operation into a linked list of operators
// Returns 0 on success, -1 on failure
int32_t parseOpr(const char *oprStr, pOpr oprHead);
