/*
 * memory.c
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#include <int.h>
#include <memory.h>
#include <log.h>

void* operator new(long unsigned int size) {
	void* thing = malloc(size);
	return thing;
}

static void destory(void* object) {
	free(object);
}

void operator delete(void* object) {
	destory(object);
}
void operator delete(void* object, unsigned long size){
	destory(object);
}
