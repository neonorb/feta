/*
 * int.h
 *
 *  Created on: May 7, 2016
 *      Author: chris
 */

#ifndef INCLUDE_INT_H_
#define INCLUDE_INT_H_

#ifndef __int8_defined
# define __int8_defined
typedef signed char             int8;
typedef short int               int16;
typedef int                     int32;
# if __WORDSIZE == 64
typedef long int                int64;
# else
__extension__
typedef long long int           int64;
# endif
#endif

/* Unsigned.  */
typedef unsigned char           uint8;
typedef unsigned short int      uint16;
#ifndef __uint32_t_defined
typedef unsigned int            uint32;
# define __uint32_t_defined
#endif
#if __WORDSIZE == 64
typedef unsigned long int       uint64;
#else
__extension__
typedef unsigned long long int  uint64;
#endif

typedef uint32 size_t;

#endif /* INCLUDE_INT_H_ */
