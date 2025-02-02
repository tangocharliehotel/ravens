:: Compile all files for ravens interpreter
set filesToCompile=main.c chunk.c memory.c debug.c value.c
gcc -std=c99 -Wall %filesToCompile% -o main