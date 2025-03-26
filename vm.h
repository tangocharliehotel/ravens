#ifndef ravens_vm_h
#define ravens_vm_h

#include "chunk.h"
#include "object.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX 64
#define STACK_MAX 256

//TODO: change so that errors go from fatal (and halt the interpertor), to just push error and enable user to recover form error

typedef struct {
	ObjClosure* closure;
	uint8_t* ip;
	Value* slots;
} CallFrame;

typedef struct {
	CallFrame frames[FRAMES_MAX];
	int frameCount; 
	
	Value stack[STACK_MAX];
	Value* stackTop; //using direct pointer as it is faster to dereference poiter than calculate offset 
					//from index each time. It always points to the last item (place for next item)
	Table strings;
	Table globals;
	ObjString* initString;
	ObjUpvalue* openUpvalues;
	
	size_t bytesAllocated;
	size_t nextGC;
	Obj* objects;
	int grayCount;
	int grayCapacity;
	Obj** grayStack;
} VM;

typedef enum {
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif
