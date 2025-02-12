:: Compile all files for ravens interpreter
set filesToCompile=main.c chunk.c memory.c debug.c value.c vm.h vm.c
gcc -std=c99 -Wall %filesToCompile% -o main