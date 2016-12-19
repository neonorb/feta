/*
 * feta.h
 *
 *  Created on: Oct 31, 2016
 *      Author: chris13524
 */

#ifndef INCLUDE_FETA_H_
#define INCLUDE_FETA_H_

#include <feta/memory.h>
#include <feta/string.h>
#include <feta/int.h>
#include <feta/bool.h>
#include <feta/log.h>

// variable is never used
#define UNUSED(x) (void)(x)

// not implemented yet (so unused), but will be used later
#define CUNUSED(x) (void)(x)

// not implemented
#define NIMPL crash(concat(__PRETTY_FUNCTION__, " not implemented yet"))

// should never happen
#define SNH crash(concat(__PRETTY_FUNCTION__, concat(" should never reach this point in ",concat(__FILE__,concat(":",toString(__LINE__, 10))))))

#endif /* INCLUDE_FETA_H_ */
