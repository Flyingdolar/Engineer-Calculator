#pragma once
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
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

// Structs
typedef struct _var_ *pVar;
typedef struct _var_ {
    char *name;    // Name of Variable
    vType format;  // Type of Variable (INT or FLOAT)
    int32_t iVal;  // Integer Value
    float fVal;    // Float Value
    pVar Next;     // Next Variable
    pVar Prev;     // Previous Variable
} sVar;

typedef struct _opr_ *pOpr;
typedef struct _opr_ {
    opType type;   // Type of Operator (or Operand)
    vType format;  // Format of Operand (INT or FLOAT)
    int32_t iVal;  // Integer Value
    float fVal;    // Float Value
    pOpr Next;     // Next Operator
    pOpr Prev;     // Previous Operator
} sOpr;

// Global Variable
const char *opStr[17] = {
    "+", "-", "*", "/", "^", "sqrt", "log", "logn", "sin", "cos", "tan", "!", "sec", "csc", "cot", "(", ")"};
pVar varHead = NULL;

// Functions in Struct.c
// 1. Initialize a head of variable linked list
pVar initVar();
pOpr initOpr();
// 2. Add a new variable to the linked list
pVar addNextVar(pVar var);
pOpr addNextOpr(pOpr opr);

pVar insertVar(pVar var, char *name, vType format);
pOpr insertOpr(pOpr opr, opType type, vType format);

// 3. Free the memory of variable linked list
void freeVar(pVar var);
void freeOpr(pOpr opr);

// Function in Calc.c
// 1. Turn a string operation into a linked list of operators
pOpr parseOpr(const char *oprStr);
// 2. Turn a string variable into a linked list of variables
void parseVar(const char *varStr, , char option);
