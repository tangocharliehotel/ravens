#ifndef ravens_compiler_h
#define ravens_compiler_h

#include "string.h"
#include "object.h"
#include "vm.h"

ObjFunction* compile(const char* source);

#endif