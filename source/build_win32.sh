# Copyright (c) 2023 James Cook

i686-w64-mingw32-gcc -c -Wall -Werror -fpic libmyeucode.c
i686-w64-mingw32-gcc -shared -o libmyeucode.dll libmyeucode.o
i686-w64-mingw32-gcc -L. -Wall -o testdll.exe main.c -lmyeucode
# You will only need to do this once:
# export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
# ./testdll
