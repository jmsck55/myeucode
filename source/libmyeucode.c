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

void printWith(const char * trace)
{
    fprintf(pFile,"with %s\n",trace);
}

void printWithOut(const char * trace)
{
    fprintf(pFile,"without %s\n",trace);
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

void printGetc(const char * fn)
{
    fprintf(pFile,"getc(%s)", fn);
}

void printGets(const char * fn)
{
    fprintf(pFile,"gets(%s)", fn);
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

void printType(const char * name, const char * args)
{
    fprintf(pFile,"type %s(%s)\n", name, args);
}
void printEndType()
{
    fputs("end type\n",pFile);
}
void printFunction(const char * name, const char * args)
{
    fprintf(pFile,"function %s(%s)\n", name, args);
}
void printEndFunction()
{
    fputs("end function\n",pFile);
}
void printProcedure(const char * name, const char * args)
{
    fprintf(pFile,"procedure %s(%s)\n", name, args);
}
void printEndProcedure()
{
    fputs("end procedure\n",pFile);
}

void printReturn(const char * retval)
{
    fprintf(pFile,"return %s\n",retval);
}

void printNamespace(const char * namespace)
{
    fprintf(pFile,"namespace %s\n", namespace);
}

void printInclude(const char * path)
{
    fprintf(pFile,"include %s\n", path);
}

void printIncludeAs(const char * path, const char * namespace)
{
    fprintf(pFile,"include %s as %s\n", path, namespace);
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

// if then, else, elsif then, end if statements

void printIfStatement(const char * condition)
{
    fprintf(pFile,"if %s then\n", condition);
}

void printElsIf(const char * condition)
{
    fprintf(pFile,"elsif %s then\n", condition);
}

void printElse()
{
    fputs("else\n",pFile);
}

void printEndIf()
{
    fputs("end if\n",pFile);
}

// for and while statements

void printForStatement(const char * iter, const char * start, const char * stop, const char * by)
{
    fprintf(pFile,"for %s = %s to %s by %s do\n", iter, start, stop, by);
}
void printEndFor()
{
    fputs("end for\n",pFile);
}

void printExitOutOfLoop()
{
    fputs("exit\n",pFile);
}
void printContinueLoop()
{
    fputs("continue\n",pFile);
}

void printWhileStatement(const char * condition)
{
    fprintf(pFile,"while %s do\n", condition);
}
void printEndWhile()
{
    fputs("end while\n",pFile);
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

void printEquals()
{
    fputs(" = ",pFile);
}

void printSubscript(const char * subscript)
{
    fprintf(pFile,"[%s]", subscript);
}

void printBraces(const char * innerBraces)
{
    fprintf(pFile,"{%s}", innerBraces);
}

void printConcat()
{
    fputs(" & ",pFile);
}

void printParentheses(const char * inner)
{
    fprintf(pFile,"(%s)", inner);
}

// More Functions and Procedures:

void printAppend()
{
    fputs("append",pFile);
}
void printPrepend()
{
    fputs("prepend",pFile);
}
void printRepeat()
{
    fputs("repeat",pFile);
}

// Builtin Routines:


void print_qm()
{
    fputs("? ",pFile);
}
void print_abort()
{
    fputs("abort",pFile);
}
void print_and_bits()
{
    fputs("and_bits",pFile);
}
void print_append()
{
    fputs("append",pFile);
}
void print_arctan()
{
    fputs("arctan",pFile);
}
void print_atom()
{
    fputs("atom",pFile);
}
void print_c_func()
{
    fputs("c_func",pFile);
}
void print_c_proc()
{
    fputs("c_proc",pFile);
}
void print_call()
{
    fputs("call",pFile);
}
void print_call_func()
{
    fputs("call_func",pFile);
}
void print_call_proc()
{
    fputs("call_proc",pFile);
}
void print_clear_screen()
{
    fputs("clear_screen",pFile);
}
void print_close()
{
    fputs("close",pFile);
}
void print_command_line()
{
    fputs("command_line",pFile);
}
void print_compare()
{
    fputs("compare",pFile);
}
void print_cos()
{
    fputs("cos",pFile);
}
void print_date()
{
    fputs("date",pFile);
}
void print_delete()
{
    fputs("delete",pFile);
}
void print_delete_routine()
{
    fputs("delete_routine",pFile);
}
void print_equal()
{
    fputs("equal",pFile);
}
void print_find()
{
    fputs("find",pFile);
}
void print_find_from()
{
    fputs("find_from",pFile);
}
void print_floor()
{
    fputs("floor",pFile);
}
void print_get_key()
{
    fputs("get_key",pFile);
}
void print_getc()
{
    fputs("getc",pFile);
}
void print_getenv()
{
    fputs("getenv",pFile);
}
void print_gets()
{
    fputs("gets",pFile);
}
void print_hash()
{
    fputs("hash",pFile);
}
void print_head()
{
    fputs("head",pFile);
}
void print_include_paths()
{
    fputs("include_paths",pFile);
}
void print_insert()
{
    fputs("insert",pFile);
}
void print_integer()
{
    fputs("integer",pFile);
}
void print_length()
{
    fputs("length",pFile);
}
void print_log()
{
    fputs("log",pFile);
}
void print_machine_func()
{
    fputs("machine_func",pFile);
}
void print_machine_proc()
{
    fputs("machine_proc",pFile);
}
void print_match()
{
    fputs("match",pFile);
}
void print_match_from()
{
    fputs("match_from",pFile);
}
void print_mem_copy()
{
    fputs("mem_copy",pFile);
}
void print_mem_set()
{
    fputs("mem_set",pFile);
}
void print_not_bits()
{
    fputs("not_bits",pFile);
}
void print_object()
{
    fputs("object",pFile);
}
void print_open()
{
    fputs("open",pFile);
}
void print_option_switches()
{
    fputs("option_switches",pFile);
}
void print_or_bits()
{
    fputs("or_bits",pFile);
}
void print_peek()
{
    fputs("peek",pFile);
}
void print_peek_string()
{
    fputs("peek_string",pFile);
}
void print_peek2s()
{
    fputs("peek2s",pFile);
}
void print_peek2u()
{
    fputs("peek2u",pFile);
}
void print_peek4s()
{
    fputs("peek4s",pFile);
}
void print_peek4u()
{
    fputs("peek4u",pFile);
}
void print_peek8s()
{
    fputs("peek8s",pFile);
}
void print_peek8u()
{
    fputs("peek8u",pFile);
}
void print_peek_longs()
{
    fputs("peek_longs",pFile);
}
void print_peek_longu()
{
    fputs("peek_longu",pFile);
}
void print_peek_pointer()
{
    fputs("peek_pointer",pFile);
}
void print_peeks()
{
    fputs("peeks",pFile);
}
void print_pixel()
{
    fputs("pixel",pFile);
}
void print_platform()
{
    fputs("platform",pFile);
}
void print_poke()
{
    fputs("poke",pFile);
}
void print_poke2()
{
    fputs("poke2",pFile);
}
void print_poke4()
{
    fputs("poke4",pFile);
}
void print_poke8()
{
    fputs("poke8",pFile);
}
void print_poke_long()
{
    fputs("poke_long",pFile);
}
void print_poke_pointer()
{
    fputs("poke_pointer",pFile);
}
void print_position()
{
    fputs("position",pFile);
}
void print_power()
{
    fputs("power",pFile);
}
void print_prepend()
{
    fputs("prepend",pFile);
}
void print_print()
{
    fputs("print",pFile);
}
void print_printf()
{
    fputs("printf",pFile);
}
void print_puts()
{
    fputs("puts",pFile);
}
void print_rand()
{
    fputs("rand",pFile);
}
void print_remainder()
{
    fputs("remainder",pFile);
}
void print_remove()
{
    fputs("remove",pFile);
}
void print_repeat()
{
    fputs("repeat",pFile);
}
void print_replace()
{
    fputs("replace",pFile);
}
void print_routine_id()
{
    fputs("routine_id",pFile);
}
void print_sequence()
{
    fputs("sequence",pFile);
}
void print_sin()
{
    fputs("sin",pFile);
}
void print_splice()
{
    fputs("splice",pFile);
}
void print_sprintf()
{
    fputs("sprintf",pFile);
}
void print_sqrt()
{
    fputs("sqrt",pFile);
}
void print_system()
{
    fputs("system",pFile);
}
void print_system_exec()
{
    fputs("system_exec",pFile);
}
void print_tail()
{
    fputs("tail",pFile);
}
void print_tan()
{
    fputs("tan",pFile);
}
void print_task_clock_start()
{
    fputs("task_clock_start",pFile);
}
void print_task_clock_stop()
{
    fputs("task_clock_stop",pFile);
}
void print_task_create()
{
    fputs("task_create",pFile);
}
void print_task_list()
{
    fputs("task_list",pFile);
}
void print_task_schedule()
{
    fputs("task_schedule",pFile);
}
void print_task_self()
{
    fputs("task_self",pFile);
}
void print_task_status()
{
    fputs("task_status",pFile);
}
void print_task_suspend()
{
    fputs("task_suspend",pFile);
}
void print_task_yield()
{
    fputs("task_yield",pFile);
}
void print_time()
{
    fputs("time",pFile);
}
void print_trace()
{
    fputs("trace",pFile);
}
void print_xor_bits()
{
    fputs("xor_bits",pFile);
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
