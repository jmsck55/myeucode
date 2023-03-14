// Copyright (c) 2023 James Cook
// testdll.c
// Test code for libmyeucode.h

#include <stdio.h>
#include <stdlib.h>

#include "libmyeucode.h"

int main()
{
    double sec;
    int error_code;

    if (LIBMYEUCODE_VERSION != dllVersion())
    {
        return 1;
    }

    if (openMain(FILENAME_EVAL_EX) != 0)
    {
        puts("Couldn't open file: " FILENAME_EVAL_EX "\n");
        return 2;
    }

    print("--");
    printWithTrace();
    print("--");
    printTrace(1);

    printPuts("1", "Hi world.\\n"); // Extra backslashes needed on these functions.

    printVariable("integer", "fn");
    printOpen("fn", FILENAME_DATA_E, "w");
    printPuts("fn", "--with trace\\n--trace(1)\\n");
    printPrintf("fn", "public object data = %d\\n", "{2 + 2}");
    printClose("fn");

    closeMain();

    error_code = executeScript(&sec, "eui", FILENAME_EVAL_EX, "");
    printf("return value from script is: %i\n", error_code);
    printf("execution time in seconds:\n%f\n", sec);
    puts("successful test run.\n");

    return 0;
}
