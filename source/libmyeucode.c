// Copyright (c) 2023 James Cook
// libmyeucode.c
// Call Euphoria code by writing a script using a "C" dynamic link library, very fast.

#include "libmyeucode.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE * pFile;

// dllVersion()

int dllVersion()
{
    return LIBMYEUCODE_VERSION;
}

// openMain() and closeMain()

int openMain(const char * filename)
{
    pFile = fopen(filename, "w");
    if (pFile == NULL)
    {
        // puts("Couldn't open file.\n");
        return 1;
    }
    return 0;
}

void closeMain()
{
    fclose(pFile);
}

// executeScript()

int executeScript(double * pseconds, const char * pathtoeui, const char * filename, const char * arguments)
{
    // pseconds can be a NULL value, or a pointer to a double in your code.
    // See explaination below:
    clock_t t, t0;
    int error_code, cx;
    char buffer[BUFFER_SIZE];
    cx = snprintf(buffer, BUFFER_SIZE, "%s %s %s", pathtoeui, filename, arguments);
    if (cx < 0 || cx >= BUFFER_SIZE)
    {
        return 999;
    }
    if (pseconds)
    {
        t0 = clock();
    }
    error_code = system(buffer);
    if (pseconds)
    {
        t = clock() - t0;
        // Store elapsed time in seconds to pointer to double, pseconds.
        // (*pseconds) dereferences pseconds to a double,
        // allowing it to store a double value in caller's code.
        // Use:
        //
        // double seconds;
        // int errorlevel = executeScript(&seconds, "eui", "myfile.ex", "arg1 arg2");
        // printf("%f\n", seconds);
        //
        (* pseconds) = (double)(((double)t) / ((double)CLOCKS_PER_SEC));
    }
    return error_code;
}

// generic line ending, with optional string:

void println(const char * line)
{
    // print to file with line ending character (\n)
    fprintf(pFile,"%s\n", line);
}

// print line, without line ending.

void print(const char * line)
{
    fputs(line,pFile);
}

// More functions as an API:

// Trace functions:

void printWithTrace()
{
    fputs("with trace\n",pFile);
}

void printWithOutTrace()
{
    fputs("without trace\n",pFile);
}

void printTrace(int one_or_zero)
{
    fprintf(pFile,"trace(%i)\n",one_or_zero);
}

// String output functions:

void printPuts(const char * fn, const char * str)
{
    fprintf(pFile,"puts(%s,\"%s\")\n", fn, str);
}

void printPrintf(const char * fn, const char * format, const char * params)
{
    fprintf(pFile,"printf(%s,\"%s\",%s)\n", fn, format, params);
}

// Constants and Variables:

void printPublic()
{
    fputs("public ",pFile);
}

void printGlobal()
{
    fputs("global ",pFile);
}

void printExport()
{
    fputs("export ",pFile);
}

void printVariable(const char * type, const char * names)
{
    fprintf(pFile,"%s %s\n", type, names);
}

void printConstant(const char * name, const char * value)
{
    fprintf(pFile,"constant %s = %s\n", name, value);
}

// open() and close() file functions

void printOpen(const char * variablename, const char * filename, const char * openmode)
{
    fprintf(pFile,"%s = open(\"%s\",\"%s\")\n", variablename, filename, openmode);
}

void printClose(const char * variablename)
{
    fprintf(pFile,"close(%s)\n", variablename);
}

// if then, end if statements

void printIfStatement(const char * condition)
{
    fprintf(pFile,"if %s then\n", condition);
}

void printEndIf()
{
    fputs("end if\n",pFile);
}

// abort statement

void printAbort(const char * errorcode)
{
    fprintf(pFile,"abort(%s)\n", errorcode);
}

// command_line()

void printCommandLine()
{
    fputs("command_line()",pFile);
}

// assignments, need a line ending using println() if not in an "if statement":

void printEquals(const char * lhs, const char * rhs)
{
    // lhs is left-hand side
    // rhs is right-hand side
    fprintf(pFile,"%s = %s", lhs, rhs);
}

void printSubscript(const char * subscript)
{
    fprintf(pFile,"[%s]", subscript);
}

// int main()
// {
//     clock_t t, t0;
//     int error_code;
//     FILE * pFile;
//     
//     t0 = clock();
// 
//     pFile = fopen(FILENAME_EVAL_EX, "w");
//     if (pFile == NULL)
//     {
//         puts("Couldn't open file.\n");
//         return 1;
//     }
//     fputs("--with trace\n--trace(1)\n",pFile);
//     fputs("puts(1, \"Hi world.\\n\")\n",pFile);
//     fprintf(pFile,"integer fn = open(\"%s\", \"w\")\n", FILENAME_DATA_E);
//     fputs("puts(fn, \"--with trace\\n--trace(1)\\n\")\n",pFile);
//     fprintf(pFile,"printf(fn, \"public object data = %%d\\n\", %d + %d)\n", 2, 2);
//     fputs("close(fn)\n",pFile);
//     fclose(pFile);
// 
//     error_code = system("eui " FILENAME_EVAL_EX);
// 
//     t = clock() - t0;
//     double sec = (double)(((double)t) / ((double)CLOCKS_PER_SEC));
//     printf("execution time in seconds\n%f\n", sec);
// 
//     return 0;
// }
