#pragma once
#include <stdio.h>

#ifdef DEBUG
#define PRINTD(...) printf(__VA_ARGS__)
#else
#define PRINTD(...)
#endif

// Some useful functions for programming in C
int printErr(const char *msg) {
    printf("\033[1;31mE:%s\n\033[0m", msg);
    return -1;
}
