/*
 * string.h
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_

namespace feta {

typedef char strchar; // TODO deprecated
typedef char Strchar;
typedef const Strchar* String;

}

#include <feta/int.h>
#include <feta/bool.h>
#include <feta/list.h>

namespace feta {

Size stringlength(String str); // TODO deprecated
Size stringLength(String str);
Boolean strequ(String one, String two); // TODO deprecated
Boolean stringEquals(String one, String two);
Boolean stringStartsWith(String string, String beginning);
String charListToString(List<Strchar>* list);
String substring(String string, uinteger start, uinteger end);
String concat(String one, String two);

String toString(int value, int base);

String operator ""_H(const Strchar* arr, Size length);

}

#endif /* INCLUDE_STRING_H_ */
