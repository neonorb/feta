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

void assert(bool b, feta::String message);

namespace fetatest {

	void test();

}
#endif

#endif /* INCLUDE_FETATEST_H_ */
