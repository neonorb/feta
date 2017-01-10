/*
 * log.cpp
 *
 *  Created on: Oct 6, 2016
 *      Author: chris13524
 */

#include <feta.h>

namespace feta {

void debug(String name, uinteger value, uint8 base) {
	debugPrint(name);
	debugPrint(": ");
	debug(toString(value, base));
}

#ifdef BITS64
void debug(String name, uint64 value) {
	debug(name, value, 16);
}
#endif

void debug(String name, uint32 value) {
	debug(name, (uinteger) value);
}

void debug(String name, void* value) {
	debug(name, (uinteger) value);
}

void debug(String message) {
	debugPrint(message);
	debugPrint("\n\r");
}

void debug(strchar message) {
	char str[] = { message, 0 };
	debugPrint(str);
}

}
