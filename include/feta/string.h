/*
 * string.h
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_

namespace feta {

typedef char strchar;
typedef const strchar* String;

}

#include <feta/int.h>
#include <feta/bool.h>
#include <feta/list.h>

namespace feta {

size stringlength(String str);
bool strequ(String one, String two);
bool stringStartsWith(String string, String beginning);
String charListToString(List<strchar>* list);
String substring(String string, uint64 start, uint64 end);
String concat(String one, String two);

String toString(int value, int base);

String operator ""_H(const strchar* arr, size length);

}

#endif /* INCLUDE_STRING_H_ */
