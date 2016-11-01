/*
 * memory.c
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#include <int.h>
#include <memory.h>
#include <feta.h>

namespace feta {

#ifdef MEMORY_LOG

#define ALLOCATED_LENGTH 4096
static void* allocatedThings[ALLOCATED_LENGTH] = { NULL };
uint64 allocatedCount;

static uinteger watchLocations[] = { };
static uinteger watchCount = sizeof(watchLocations) / sizeof(uinteger);

void stop() {
}

/**
 * Prints each thing allocated
 */
void dumpAllocated() {
	debug("-----------------------------");
	for (uint64 i = 0; i < ALLOCATED_LENGTH; i++) {
		if (allocatedThings[i] != NULL) {
			debug("ALLOCATED", (uint64) allocatedThings[i]);
		}
	}
	debug("-----------------------------");
}

uint64 getAllocatedCount() {
	return allocatedCount;
}
#endif

void* create(long unsigned int size) {
	// allocate memory
	void* thing = fetaimpl::malloc(size);

#ifdef MEMORY_LOG
	// log the allocation
	for (uint64 i = 0; i < ALLOCATED_LENGTH; i++) {
		if (allocatedThings[i] == NULL) {
			allocatedThings[i] = thing;
			allocatedCount++;
			break;
		}
		if (i == ALLOCATED_LENGTH - 1) {
			crash("out of space for allocations - increase array size or turn off memory logging");
		}
	}

	// check if these is being watched, if so, stop
	for (uint64 i = 0; i < watchCount; i++) {
		if (watchLocations[i] == (uint64) thing) {
			stop();
			break;
		}
	}
#endif

	// return
	return thing;
}

void destroy(void* object) {
	// free memory
	fetaimpl::free(object);

	// unlog the allocation
	for (uint64 i = 0; i < ALLOCATED_LENGTH; i++) {
		if (allocatedThings[i] == object) {
			allocatedThings[i] = NULL;
			allocatedCount--;
			break;
		}
	}
}

}

void* operator new(unsigned long size) {
	return feta::create(size);
}

void operator delete(void* object) {
	feta::destroy(object);
}
void operator delete(void* object, unsigned long size) {
	UNUSED(size);

	feta::destroy(object);
}
