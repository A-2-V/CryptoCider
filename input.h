#ifndef _A2V_INPUT_H_
#define _A2V_INPUT_H_


/** REQUIRED HEADERS **/
#include <stdio.h>
#include <stdlib.h>
#include "crypto.h"

/** CONSTANTS **/
#define PASSWORD_SIZE_STD 33 /* Password string size */
#define A2V_str_standart_size 256 /* Default size of string */


/** STRUCT SAMPLES **/
extern struct st_sample_file_info {
    char * _name;
    FILE * _ptr;
    unsigned long long int _size;
};

/** PROTOTYPES **/
/*  Creating a dynamically sized string

    Arguments:
        p_file -- a stream from which a program reads its input data
        p_length -- returned length of a password
        p_alphabeth -- a string with allowed characters
        i_str_size_limit -- max size of a string */
extern char * f_str_input_dynamic(FILE const * p_file, int * const p_length, char const * const p_alphabeth, int const i_str_size_limit);

/* Searching for a label in a file and reading the text

    Arguments:
        p_file -- a stream from which a program reads its input data
        p_alphabeth -- a string with allowed characters
        p_str_searched -- a label */
extern char * f_str_search(FILE const * const p_file, char const * const p_alphabeth, char const * const p_str_searched);

extern struct st_sample_file_info * f_file_info_create(void);

extern int f_file_open(struct st_sample_file_info * p_file);

extern unsigned long long int f_file_size(FILE * p_file);

#endif // _A2V_INPUT_H_
