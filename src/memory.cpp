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

#define watchCount 0
#if watchCount > 0
static uint64 watchLocations[] = {};
#endif

void stop() {
}

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
	void* thing = fetaimpl::malloc(size);
#ifdef MEMORY_LOG
	for (uint64 i = 0; i < ALLOCATED_LENGTH; i++) {
		if (allocatedThings[i] == NULL) {
			allocatedThings[i] = thing;
			allocatedCount++;
			break;
		}
	}
#if watchCount > 0
	for (uint64 i = 0; i < watchCount; i++) {
		if (watchLocations[i] == (uint64) thing) {
			stop();
			break;
		}
	}
#endif
#endif
	return thing;
}

void destroy(void* object) {
	fetaimpl::free(object);
#ifdef MEMORY_LOG
	for (uint64 i = 0; i < ALLOCATED_LENGTH; i++) {
		if (allocatedThings[i] == object) {
			allocatedThings[i] = NULL;
			allocatedCount--;
			break;
		}
	}
#endif
}

}

void* operator new(long unsigned int size) {
	return feta::create(size);
}

void operator delete(void* object) {
	feta::destroy(object);
}
void operator delete(void* object, unsigned long size) {
	UNUSED(size);

	feta::destroy(object);
}
