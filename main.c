#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "crypto.h"

#define CHANGE_CODEPAGE system("chcp 1251")

int main(int argc, char * argv[])
{
    CHANGE_CODEPAGE;

    struct st_sample_password_info * p_password = f_st_pass_create();

    printf("%d: %s\n", p_password->i_password_length, p_password->p_ch_password);


    return 0;
}
