/*
 * list.c
 *
 *  Created on: May 8, 2016
 *      Author: chris
 */

#include <feta.h>

namespace feta {

void _outOfBounds(uinteger index, uinteger size) {
	debug("index", index);
	debug("size", size);
	crash(INDEX_OUT_OF_BOUNDS);
}

void _abort(String message) {
	crash(message);
}

}
