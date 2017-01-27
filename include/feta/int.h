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

// ---- TODO deprecated

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

// ----

// signed
typedef signed char Int8;
typedef signed short Int16;
typedef signed int Int32;
#ifdef BITS64
typedef signed long Int64;
typedef Int64 Integer;
#else
typedef Int32 Integer;
#endif

// unsigned
typedef unsigned char UInt8;
typedef unsigned short UInt16;
typedef unsigned int UInt32;
#ifdef BITS64
typedef unsigned long UInt64;
typedef UInt64 UInteger;
#else
typedef UInt32 UInteger;
#endif

typedef UInteger Size;

typedef UInt8 Boolean;

}

#endif /* INCLUDE_INT_H_ */
