/*
 * errors.h
 *
 *  Created on: May 4, 2016
 *      Author: chris
 */

#ifndef INCLUDE_ERRORS_H_
#define INCLUDE_ERRORS_H_

#include <string.h>

#define INDEX_OUT_OF_BOUNDS L"index-out-of-bounds" // thrown when you try to access an index that is out of bounds

#define MEMORY_ALLOCATOR_UNDEFINED L"memory-allocator-undefined" // thrown when memory allocation is requested, but no allocator has been set
#define ALLOCATE_FAILED L"allocate-failed" // thrown when the allocator could not find a suitable location to put memory
#define FREE_FAILED L"free-failed" // thrown when memory could not be freed
#define FREE_FAILED_FREED_ALREADY L"free-failed-freed-already" // thrown when memory could not be freed because it was freed already

void crash(String message);

#endif /* INCLUDE_ERRORS_H_ */
