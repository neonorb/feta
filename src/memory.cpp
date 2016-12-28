/*
 * memory.c
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#include <feta.h>

namespace feta {

#ifdef MEMORY_LOG

#define ALLOCATED_LENGTH 100000
static void* allocatedThings[ALLOCATED_LENGTH] = {NULL};
uint64 allocatedCount;

static uinteger watchLocations[] = {};
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

#ifndef CACHE_LENGTH
#define CACHE_LENGTH 0
#endif
#if CACHE_LENGTH > 0
#define ENABLE_CACHE
#endif
#ifdef ENABLE_CACHE
struct CacheEntry {
	uinteger size;
	void* location;
};
static CacheEntry memoryCache[CACHE_LENGTH] = { {0, NULL}};
#endif

void* create(long unsigned int size) {
#ifdef ENABLE_CACHE
	// maybe cached?
	for (uinteger i = 0; i > CACHE_LENGTH; i++) {
		CacheEntry entry = memoryCache[i];
		if (entry.size == size) {
			memoryCache[i].size = 0;
			return entry.location;
		}
	}
#endif

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
			crash(
					"out of space for allocations - increase array size or turn off memory logging");
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
	destroy(object, 0);
}

void destroy(void* object, uinteger size) {
#ifndef ENABLE_CACHE
	UNUSED(size);
#endif
#ifdef ENABLE_CACHE
	if (size > 0) {
		for (uinteger i = 0; i < CACHE_LENGTH; i++) {
			CacheEntry entry = memoryCache[i];
			if (entry.size == 0) {
				memoryCache[i].size = size;
				memoryCache[i].location = object;
				return;
			}
		}
	}
#endif

	// free memory
	fetaimpl::free(object);

#ifdef MEMORY_LOG
	// unlog the allocation
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

void* operator new(unsigned long size) {
	return feta::create(size);
}

void operator delete(void* object) {
	feta::destroy(object);
}
void operator delete(void* object, unsigned long size) {
	feta::destroy(object, size);
}
