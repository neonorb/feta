/*
 * memory.c
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#include <memory.h>
#include <errors.h>

uint8* defaultMemoryAllocator(size_t size){
	throw MEMORY_ALLOCATOR_UNDEFINED;
}

static MemoryManager memoryManager = {&defaultMemoryAllocator};

void setMemoryManager(MemoryManager memManger){
	memoryManager = memManger;
}

void* getMemory(unsigned int size){
	return memoryManager.allocate(size);
}
