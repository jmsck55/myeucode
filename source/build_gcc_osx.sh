# Copyright (c) 2023 James Cook

gcc -c -Wall -Werror -fpic libmyeucode.c
gcc -shared -o libmyeucode.dylib libmyeucode.o
gcc -L. -Wall -o testdll testdll.c -lmyeucode
# You will only need to do this once:
# export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
# ./testdll
