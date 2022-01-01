/*****************************************************************************/
/* Title                 :   STD_TYPES                                       */
/* Filename              :   STD_TYPES.h                                     */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Sep 7, 2021                                     */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw GCC                                       */
/* Notes                 :   None                                            */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/****************************   FILE GUARDE  *********************************/
#ifndef  STD_TYPES_H
#define  STD_TYPES_H


/*============================================================================*/
/* BASIC DATA TYPES.                                                          */
/*============================================================================*/


                                                      /*         From ...... Up-to                 */
typedef unsigned char           u8  ;                 /*            0 ...... 255                   */
typedef unsigned short          u16 ;                 /*            0 ...... +65535                */
typedef unsigned int            u32 ;                 /*            0 ...... 4294967295            */
typedef unsigned long           u64 ;                 /*            0 ......18446744073709551615   */

typedef signed char             s8  ;                 /*         -128 ...... +127                  */
typedef signed short            s16 ;                 /*       -32768 ...... +32767                */
typedef signed int    		    s32 ;                 /*  -2147483648 ...... 214748,3647           */
typedef signed long             s64 ;

typedef float                   f32;
typedef double                  f64;
typedef long double             f128;

#define NULL ((void*)0x00)

#endif   /*STD_TYPES_H*/