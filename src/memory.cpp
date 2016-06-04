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
	return malloc(size);
}

static void destory(void* object) {
	Deleteable* deleteable = (Deleteable*) object;
	if(deleteable->magic != 0xAAFF){
		crash("trying to delete object thats not deletable");
	}
	deleteable->destroy();

	free(object);
}

void operator delete(void* object) {
	destory(object);
}
void operator delete(void* object, unsigned long size){
	destory(object);
}
