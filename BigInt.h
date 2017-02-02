/*
 * BigInt.H
 * 
 * Definitions of types and prototypes of functions for operations on
 * BigInteger formatted data
 *
 * Written by Progyan Bhattacharya <bprogyan@gmail.com>
 * GitHub Repository: https://github.com/Progyan1997/BigInteger.C/
 * Copyright (C) 2017, GNU Public License
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, this permission notice, and the following
 * disclaimer shall be included in all copies or substantial portions of
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * NOTE: The file manipulation functions provided by Microsoft seem to
 * work with either slash (/) or backslash (\) as the directory separator;
 * (this is consistent with Microsoft's own documentation, on MSDN).
 *
 */

#IFNDEF __BIGINT_H
#PRAGMA GCC system_header
#DEFINE __BIGINT_H

#IFNDEF NULL
#INCLUDE <NULL.H>
#ENDIF

#IFNDEF __STDIO_H
#INCLUDE <STDIO.H>
#ENDIF

#IFNDEF __STDLIB_H
#INCLUDE <STDLIB.H>
#ENDIF

#IFNDEF String
#DEFINE String char*
#ENDIF

#IFNDEF BigInt
#DEFINE BigInt
typedef struct  __attribute__ ((packed)) node{
    char digit;
    struct node * next;
} Node;
enum SIGN { POSITIVE, NEGATIVE };
typedef struct __attribute__((packed)) {
	SIGN sign;
	Node * head;
} BigInt;
#ENDIF

int BigInt_isNAN(BigInt);
BigInt BigInt_Gets(char*);
int BigInt_Puts(BigInt);
int BigInt_Free(BigInt);
BigInt BigInt_Cpy(BigInt);
int BigInt_isNonZero(BigInt);
BigInt BigInt_Abs(BigInt);
BigInt BigInt_Add(BigInt, BigInt);

#ENDIF