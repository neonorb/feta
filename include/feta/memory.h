/*
 * memory.h
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#undef NULL
#define NULL 0

// use this when the return value is not used
#define VALUE_NOT_USED NULL

#include <feta/int.h>
#include <feta/bool.h>
#include <feta/log.h>

namespace fetaimpl {

void* malloc(feta::size);
//void *realloc(void*, size_t);
//void *calloc(size_t, size_t);
void free(void*);

}

namespace feta {

//#define MEMORY_LOG // TODO remove

#ifdef MEMORY_LOG
uinteger getAllocatedCount();
void dumpAllocated();
#endif

void* create(feta::size size);
void destroy(void* object);
void destroy(void* object, feta::size size);

}

void* operator new(feta::size size);
void operator delete(void* object);
void operator delete(void* object, feta::size size);

#endif /* INCLUDE_MEMORY_H_ */
