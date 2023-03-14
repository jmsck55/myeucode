// Copyright (c) 2023 James Cook
// libmyeucode.h
// Call Euphoria code by writing a script using a "C" dynamic link library, very fast.

#ifndef LIBMYEUCODE_H
#define LIBMYEUCODE_H

#define FILENAME_EVAL_EX "eval.ex"
#define FILENAME_DATA_E "data.e"

#define BUFFER_SIZE 1024

#define LIBMYEUCODE_VERSION 2

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

extern void printWith(const char * trace);
extern void printWithOut(const char * trace);
extern void printTrace(int one_or_zero);

// String output functions:

extern void printPuts(const char * fn, const char * str);
extern void printPrintf(const char * fn, const char * format, const char * params);
extern void printGetc(const char * fn);
extern void printGets(const char * fn);

// Constants and Variables:

extern void printPublic();
extern void printGlobal();
extern void printExport();
extern void printVariable(const char * type, const char * names);
extern void printConstant(const char * name, const char * value);
extern void printType(const char * name, const char * args);
extern void printFunction(const char * name, const char * args);
extern void printProcedure(const char * name, const char * args);
extern void printEndType();
extern void printEndFunction();
extern void printEndProcedure();
extern void printReturn(const char * retval);

extern void printNamespace(const char * namespace);
extern void printInclude(const char * path);
extern void printIncludeAs(const char * path, const char * namespace);

// open() and close() file functions

extern void printOpen(const char * variablename, const char * filename, const char * openmode);
extern void printClose(const char * variablename);

// if then, end if statements

extern void printIfStatement(const char * condition);
extern void printElsIf(const char * condition);
extern void printElse();
extern void printEndIf();

// for and while statements

extern void printForStatement(const char * iter, const char * start, const char * stop, const char * by);
extern void printEndFor();

extern void printExitOutOfLoop();
extern void printContinueLoop();

extern void printWhileStatement(const char * condition);
extern void printEndWhile();

// abort statement

extern void printAbort(const char * errorcode);

// command_line()

extern void printCommandLine();

// assignments, need a line ending using println() if not in an "if statement":

extern void printEquals();
extern void printSubscript(const char * subscript);
extern void printBraces(const char * innerBraces);
extern void printConcat();
extern void printParentheses(const char * inner);

// More Functions and Procedures:

extern void printAppend();
extern void printPrepend();
extern void printRepeat();

// Builtin Routines:

extern void print_qm();
extern void print_abort();
extern void print_and_bits();
extern void print_append();
extern void print_arctan();
extern void print_atom();
extern void print_c_func();
extern void print_c_proc();
extern void print_call();
extern void print_call_func();
extern void print_call_proc();
extern void print_clear_screen();
extern void print_close();
extern void print_command_line();
extern void print_compare();
extern void print_cos();
extern void print_date();
extern void print_delete();
extern void print_delete_routine();
extern void print_equal();
extern void print_find();
extern void print_find_from();
extern void print_floor();
extern void print_get_key();
extern void print_getc();
extern void print_getenv();
extern void print_gets();
extern void print_hash();
extern void print_head();
extern void print_include_paths();
extern void print_insert();
extern void print_integer();
extern void print_length();
extern void print_log();
extern void print_machine_func();
extern void print_machine_proc();
extern void print_match();
extern void print_match_from();
extern void print_mem_copy();
extern void print_mem_set();
extern void print_not_bits();
extern void print_object();
extern void print_open();
extern void print_option_switches();
extern void print_or_bits();
extern void print_peek();
extern void print_peek_string();
extern void print_peek2s();
extern void print_peek2u();
extern void print_peek4s();
extern void print_peek4u();
extern void print_peek8s();
extern void print_peek8u();
extern void print_peek_longs();
extern void print_peek_longu();
extern void print_peek_pointer();
extern void print_peeks();
extern void print_pixel();
extern void print_platform();
extern void print_poke();
extern void print_poke2();
extern void print_poke4();
extern void print_poke8();
extern void print_poke_long();
extern void print_poke_pointer();
extern void print_position();
extern void print_power();
extern void print_prepend();
extern void print_print();
extern void print_printf();
extern void print_puts();
extern void print_rand();
extern void print_remainder();
extern void print_remove();
extern void print_repeat();
extern void print_replace();
extern void print_routine_id();
extern void print_sequence();
extern void print_sin();
extern void print_splice();
extern void print_sprintf();
extern void print_sqrt();
extern void print_system();
extern void print_system_exec();
extern void print_tail();
extern void print_tan();
extern void print_task_clock_start();
extern void print_task_clock_stop();
extern void print_task_create();
extern void print_task_list();
extern void print_task_schedule();
extern void print_task_self();
extern void print_task_status();
extern void print_task_suspend();
extern void print_task_yield();
extern void print_time();
extern void print_trace();
extern void print_xor_bits();

// here, add "include" folder, and standard library routines


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
