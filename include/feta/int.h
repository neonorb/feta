/*
 * int.h
 *
 *  Created on: May 7, 2016
 *      Author: chris
 */

#ifndef INCLUDE_INT_H_
#define INCLUDE_INT_H_

namespace feta {

#ifdef EOF
#undef EOF
#endif
#define EOF '\4'

// signed
typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
#ifdef BITS64
typedef signed long int64;
typedef int64 integer;
#else
typedef int32 integer;
#endif

// unsigned
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
#ifdef BITS64
typedef unsigned long uint64;
typedef uint64 uinteger;
#else
typedef uint32 uinteger;
#endif

typedef uinteger size;

}

#endif /* INCLUDE_INT_H_ */
