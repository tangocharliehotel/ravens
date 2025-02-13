#ifndef ravens_compiler_h
#define ravens_compiler_h

#include "string.h"
#include "object.h"
#include "vm.h"

bool compile(const char* source, Chunk* chunk);

#endif