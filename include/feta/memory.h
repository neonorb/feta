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

// dynamic initialization
// use it like so: DYNAMIC_INIT(clazz, Class(<args>))
// destrutors are NOT supported, use this just for basic initializers
typedef void (*InitFunc)();
#define INIT_FUNCN(n, f) __attribute__((section("dynamicInit"))) InitFunc _##n##init_ptr = f;
#define INIT_FUNC(f) INIT_FUNCN(f, f)
#define DYNAMIC_INIT(n, c) \
		void __dynamicInit_##n () { n = c; } \
		INIT_FUNC(__dynamicInit_##n)

void dynamicInit(uinteger offset);
inline void dynamicInit() {
	dynamicInit(0);
}

}

extern feta::InitFunc __start_dynamicInit;
extern feta::InitFunc __stop_dynamicInit;

void* operator new(feta::size size);
void* operator new[](feta::size size);
void operator delete(void* object);
void operator delete(void* object, feta::size size);
void operator delete[](void* object);
void operator delete[](void* object, feta::size size);

#endif /* INCLUDE_MEMORY_H_ */
