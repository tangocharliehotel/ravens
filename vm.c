#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

//Todo: change from static VM to do explicitly take VM pointer and pass it around
//Todo: When scaling up, go away from global variables and pass a pointer to every single function instead
/*Might be a good challenge to change this from a stack-based bytecode to register-based.*/

VM vm;

static void resetStack() {
	//as stack array is decleared directly inline in VM Struct, no need to allocate it
	//just point to the beginning of array to indicate it is empty
	vm.stackTop = vm.stack; 
}

void initVM() {
	resetStack();
}

void freeVM() {
}

void push(Value value) {
	*vm.stackTop = value;
	vm.stackTop++;
}

Value pop() {
	vm.stackTop--;
	return *vm.stackTop;
}

static InterpretResult run() {
	/* This decoding/dispatching could also be done by other techniques (direct threaded code, jump table, computed goto.
	It can also be mad efaster by writing it in assembly. Maybe a lesson for later*/
	#define READ_BYTE() (*vm.ip++) //macro for read byte of the next IP to be run
	#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()]) //macro to read out constant within chunk at byte
	#define BINARY_OP(op)	\
		do {	\
			double b = pop();	\
			double a = pop();	\
			push(a op b);	\
		} while (false)
	
		for (;;) {
	#ifdef DEBUG_TRACE_EXECUTION
			printf("		");
			for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
				printf("[ ");
				printValue(*slot);
				printf(" ]");
			}
			printf("\n");
			disassembleInstruction(vm.chunk,
									(int)(vm.ip - vm.chunk->code));
	#endif
			uint8_t instruction;
			switch (instruction = READ_BYTE()) {
				case OP_CONSTANT: {
					Value constant = READ_CONSTANT();
					push(constant);
					break;
				}
				case OP_ADD: BINARY_OP(+); break;
				case OP_SUBTRACT: BINARY_OP(-); break;
				case OP_MULTIPLY: BINARY_OP(*); break;
				case OP_DIVIDE: BINARY_OP(/); break;
				case OP_NEGATE: push(-pop()); break;
				case OP_RETURN: {
					printValue(pop());
					printf("\n");
					return INTERPRET_OK;
				}
			}
	#undef READ_BYTE
	#undef READ_CONSTANT
	#undef BINARY_OP
		}
}

InterpretResult interpret(Chunk* chunk) {
	vm.chunk = chunk;
	vm.ip = vm.chunk->code;
	return run();
}