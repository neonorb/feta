/*
 * fetatest.h
 *
 *  Created on: Nov 1, 2016
 *      Author: chris13524
 */

#ifndef INCLUDE_FETATEST_H_
#define INCLUDE_FETATEST_H_

#ifdef ALLOW_TEST
#include <string.h>

void _assert(feta::Boolean condition, feta::String message);
#define assert(condition, message) _assert(condition, "Assertion failed @ " __FILE__ ":" STR(__LINE__) " : " message)

namespace fetatest {

	void test();

}
#endif

#endif /* INCLUDE_FETATEST_H_ */
