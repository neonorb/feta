/*
 * memory.h
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#include <int.h>
#include <bool.h>
#include <log.h>

#define NULL 0

#define MEMORY_LOG

#ifdef MEMORY_LOG
void dumpAllocated();
#endif

//void *malloc(size_t);
//void *realloc(void*, size_t);
//void *calloc(size_t, size_t);
//void free(void *);

void* create(long unsigned int size);
void destroy(void*);

void* operator new(long unsigned int size);
void operator delete(void* object);
void operator delete(void* object, unsigned long size);

#endif /* INCLUDE_MEMORY_H_ */
