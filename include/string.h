/*
 * string.h
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_

#include <int.h>
#include <bool.h>

namespace feta {

typedef char strchar;
typedef const strchar* String;

size strlen(String str);
bool strequ(String one, String two);
bool stringStartsWith(String string, String beginning);

String substring(String string, uint64 start, uint64 end);

String toString(int value, int base);

String operator ""_H(const strchar* arr, size length);

}

#endif /* INCLUDE_STRING_H_ */
