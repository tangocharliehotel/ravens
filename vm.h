#ifndef ravens_vm_h
#define ravens_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
	Chunk* chunk;
	uint8_t* ip; //instruction pointer to keep track of instruction to be currently being executed by VM
	Value stack[STACK_MAX];
	Value* stackTop; //using direct pointer as it is faster to dereference poiter than calculate offset 
					//from index each time. It always points to the last item (place for next item)
} VM;

typedef enum {
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();

#endif
