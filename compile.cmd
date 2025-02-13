:: Compile all files for ravens interpreter
set filesToCompile=main.c chunk.c memory.c debug.c value.c vm.h vm.c compiler.h compiler.c scanner.h scanner.c object.h object.c
gcc -std=c99 -Wall %filesToCompile% -o main