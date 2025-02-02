#ifndef ravens_memory_h
#define ravens_memory_h

#include "common.h"

//wrappers to call reallocate
/*doubles the capacity value of a given array when full*/
#define GROW_CAPACITY(capacity) \
	((capacity) < 8 ? 8 : (capacity) * 2)

/*frees memory by passing zero for new size*/
#define FREE_ARRAY(type, pointer, oldCount) \
	reallocate(pointer, sizeof(type) * (oldCount), 0)

/*grows the array with the give capacity value*/	
#define GROW_ARRAY(type, pointer, oldCount, newCount) \
	(type*)reallocate(pointer, sizeof(type) * (oldCount), \
		sizeof(type) * (newCount))

void* reallocate(void* pointer, size_t oldSize, size_t newSize);
	
#endif