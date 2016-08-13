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

typedef const wchar_t* String;

size_t strlen(String str);
bool strequ(String one, String two);
bool stringStartsWith(String string, String beginning);

String substring(String string, uint64 start, uint64 end);

#endif /* INCLUDE_STRING_H_ */
