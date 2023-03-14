// Copyright (c) 2023 James Cook
// libmyeucode.h
// Call Euphoria code by writing a script using a "C" dynamic link library, very fast.

#ifndef LIBMYEUCODE_H
#define LIBMYEUCODE_H

#define FILENAME_EVAL_EX "eval.ex"
#define FILENAME_DATA_E "data.e"

#define BUFFER_SIZE 1024

#define LIBMYEUCODE_VERSION 1

// dllVersion(), compare this header version with dll's binary version.
// Don't use library if they are not the same.
// Get an updated header and dll from a git repository, such as github.com
// Search for "myeucode" on github.com

extern int dllVersion();

// openMain() and closeMain()

extern int openMain(const char * filename);
extern void closeMain();

// executeScript()

extern int executeScript(double * pseconds, const char * pathtoeui, const char * filename, const char * arguments);

// generic line ending, with optional string:

extern void println(const char * line);

// print line, without line ending.

extern void print(const char * line);

// More functions as an API:

// Trace functions:

extern void printWithTrace();
extern void printWithOutTrace();
extern void printTrace(int one_or_zero);

// String output functions:

extern void printPuts(const char * fn, const char * str);
extern void printPrintf(const char * fn, const char * format, const char * params);

// Constants and Variables:

extern void printPublic();
extern void printGlobal();
extern void printExport();
extern void printVariable(const char * type, const char * names);
extern void printConstant(const char * name, const char * value);

// open() and close() file functions

extern void printOpen(const char * variablename, const char * filename, const char * openmode);
extern void printClose(const char * variablename);

// if then, end if statements

extern void printIfStatement(const char * condition);
extern void printEndIf();

// abort statement

extern void printAbort(const char * errorcode);

// command_line()

extern void printCommandLine();

// assignments, need a line ending using println() if not in an "if statement":

extern void printEquals(const char * lhs, const char * rhs);
extern void printSubscript(const char * subscript);

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

#endif // LIBMYEUCODE_H
