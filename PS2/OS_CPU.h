/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                           (c) Copyright 2002, Nathan Brown, Longview, TX
*                                      http://www.sputnickonline.com/
*                                          All Rights Reserved
*
*                                       PIC18xxxx Specific Code
*                                       V1.00 - October 27, 2002
*
* File : OS_CPU.H
* By   : Nathan Brown, modified by John Leung for CCS PICC complier for low & mid - range CPUs
* Web  : www.techtoys.com.hk
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              DATA TYPES
*                               (Compiler Specific, CCS PICC in this case)
*********************************************************************************************************
*/

/* #define BOOLEAN short int (8 bits, -128<->127) as per 16F877A */
typedef unsigned char  		INT8U;                    /* Unsigned  8 bit quantity */
typedef signed   char  		INT8S;                    /* Signed    8 bit quantity */
typedef unsigned long int   INT16U;                   /* Unsigned 16 bit quantity */
typedef long int			INT16S;                   /* Signed   16 bit quantity */
typedef unsigned int32  	INT32U;                   /* Unsigned 32 bit quantity */
typedef signed int32  		INT32S;                   /* Signed   32 bit quantity */
typedef float          		FP32;                     /* Single precision floating point */

/* end */
