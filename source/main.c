// Copyright (c) 2023 James Cook
// Call Euphoria code by writing a script using "C", very fast.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME_EVAL_EX "eval.ex"
#define FILENAME_DATA_E "data.e"

int main()
{
    clock_t t, t0;
    int error_code;
    FILE * pFile;

    pFile = fopen(FILENAME_EVAL_EX, "w");
    if (pFile == NULL)
    {
        puts("Couldn't open file.\n");
        return 1;
    }
    fputs("--with trace\n--trace(1)\n",pFile);
    fputs("puts(1, \"Hi world.\\n\")\n",pFile);
    fprintf(pFile,"integer fn = open(\"%s\", \"w\")\n", FILENAME_DATA_E);
    fputs("puts(fn, \"--with trace\\n--trace(1)\\n\")\n",pFile);
    fprintf(pFile,"printf(fn, \"public object data = %%d\\n\", {%d + %d})\n", 2, 2);
    fputs("close(fn)\n",pFile);
    fclose(pFile);

    t0 = clock();

    error_code = system("eui " FILENAME_EVAL_EX);

    t = clock() - t0;
    double sec = (double)(((double)t) / ((double)CLOCKS_PER_SEC));
    printf("execution time in seconds\n%f\n", sec);

    return 0;
}
