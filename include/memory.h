/*
 * memory.h
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#include <int.h>

typedef uint8* (*MemoryAllocate)(size_t);

struct MemoryManager {
	MemoryAllocate allocate;
};

void setMemoryManager(MemoryManager memManger);

void* getMemory(unsigned int size);

#endif /* INCLUDE_MEMORY_H_ */
