/*
 * memory.c
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#include <int.h>
#include <memory.h>
#include <log.h>

void *malloc(size_t);
void *realloc(void*, size_t);
void *calloc(size_t, size_t);
void free(void *);

#ifdef MEMORY_LOG
#define ALLOCATED_LENGTH 4096
static void* allocatedThings[ALLOCATED_LENGTH] = { NULL };
#define watchCount 1
static uint64 watchLocations[] = { };
uint64 allocatedCount;

void stop() {
}

void dumpAllocated() {
	debug(L"-----------------------------");
	for (uint64 i = 0; i < ALLOCATED_LENGTH; i++) {
		if (allocatedThings[i] != NULL) {
			debug(L"ALLOCATED", (uint64) allocatedThings[i]);
		}
	}
	debug(L"-----------------------------");
}

uint64 getAllocatedCount() {
	return allocatedCount;
}
#endif

void* create(long unsigned int size) {
	void* thing = malloc(size);
#ifdef MEMORY_LOG
	for (uint64 i = 0; i < ALLOCATED_LENGTH; i++) {
		if (allocatedThings[i] == NULL) {
			allocatedThings[i] = thing;
			break;
		}
	}
	for (uint64 i = 0; i < watchCount; i++) {
		if (watchLocations[i] == (uint64) thing) {
			stop();
			break;
		}
	}
	allocatedCount++;
#endif
	return thing;
}

void destroy(void* object) {
	free(object);
#ifdef MEMORY_LOG
	for (uint64 i = 0; i < ALLOCATED_LENGTH; i++) {
		if (allocatedThings[i] == object) {
			allocatedThings[i] = NULL;
			break;
		}
	}
	allocatedCount--;
#endif
}

void* operator new(long unsigned int size) {
	return create(size);
}

void operator delete(void* object) {
	destroy(object);
}
void operator delete(void* object, unsigned long size) {
	destroy(object);
}
