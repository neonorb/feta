/*
 * list.c
 *
 *  Created on: May 8, 2016
 *      Author: chris
 */

#include <feta.h>

namespace feta {

void _outOfBounds(uint64 index, uint64 size) {
	debug("index", index);
	debug("size", size);
	crash(INDEX_OUT_OF_BOUNDS);
}

void _abort(String message) {
	crash(message);
}

}
