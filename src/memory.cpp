/*
 * memory.c
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#include <memory.h>
#include <errors.h>

void* defaultMemoryAllocator(size_t size){
	crash(MEMORY_ALLOCATOR_UNDEFINED);

	return 0;
}

static MemoryManager memoryManager = {&defaultMemoryAllocator};

void setMemoryManager(MemoryManager memManger){
	memoryManager = memManger;
}

void* getMemory(size_t size){
	return memoryManager.allocate(size);
}
