#ifndef _A2V_CRYPTO_H_
#define _A2V_CRYPTO_H_

/** REQUIRED HEADERS **/
#include <stdio.h>
#include <stdlib.h>
#include "input.h"




/** CONSTANTS **/
#define PASSWORD_SIZE_STD 33 /* Password string size */



extern struct st_sample_password_info {
    char * p_ch_password;
    int i_password_length;
};

/** PROTOTYPES **/

extern struct st_sample_password_info * f_st_pass_create(void);
extern void f_st_pass_delete(struct st_sample_password_info * p_st_password_info);

#endif // _A2V_CRYPTO_H_
