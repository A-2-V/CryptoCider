#ifndef _A2V_INPUT_H_

#define _A2V_INPUT_H_


/** REQUIRED HEADERS **/
#include <stdio.h>
#include <stdlib.h>
#include "crypto.h"

/** CONSTANTS **/
#define PASSWORD_SIZE_STD 33 /* Password string size */
#define A2V_str_standart_size 256 /* Default size of string */

/** PROTOTYPES **/
/*  Creating a dynamically sized string

    Arguments:
        p_file -- a stream from which a program reads its input data
        p_str_size -- returned size of a string
        p_alphabeth -- a string with allowed characters
        i_str_size_limit -- max size of a string */
extern char * f_str_input_dynamic(FILE const * p_file, int * const p_str_size, char const * const p_alphabeth, int const i_str_size_limit);

#endif // _A2V_INPUT_H_
