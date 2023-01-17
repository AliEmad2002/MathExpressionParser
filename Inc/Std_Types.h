/*
 * Std_Types.h
 *
 *  Created on:	Jul 26, 2022
 *  Author:		Ali Emad Ali
 *
 *  References:
 *  	https://developer.arm.com/documentation/dui0375/g/C-and-C---Implementation-Details/Basic-data-types-in-ARM-C-and-C--
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#define false						0
#define true						1

/*	8-bit	*/
typedef signed char					s8;
typedef unsigned char				b8;
typedef unsigned char				u8;

/*	16-bit	*/
typedef short						s16;
typedef unsigned short				u16;

/*	32-bit	*/
typedef int							s32;	// i.e.: long
typedef unsigned int				u32;	// i.e.: unsigned long
typedef float						f32;
/*	all pointers are of 32-bit, too	*/

/*	64-bit	*/
typedef long long					s64;
typedef unsigned long long			u64;

/*	64-bit	*/
typedef long long					s64;
typedef unsigned long long			u64;
typedef double						d64;
typedef long double					ld64;

/*	NULL	*/
#ifndef NULL
#define NULL	0
#endif

/*	pointer to function that takes and returns void	*/
typedef void (*vvFunc_t)(void);

/*	pointer to function that takes and returns double	*/
typedef double (*ddFunc_t)(double);

#endif /* STD_TYPES_H_ */
