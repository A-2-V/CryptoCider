#include <stdio.h>
#include <stdlib.h>
#include "crypto.h"





/**–≈јЋ»«ј÷»я**/
extern struct st_sample_password_info * f_st_pass_create(void)
{
    auto struct st_sample_password_info * p_st_password_info = (struct st_sample_password_info *) malloc(sizeof(struct st_sample_password_info));

    if (p_st_password_info == NULL) {
        fprintf(stderr, "[FILE %s, LINE %d] Ќе удалось выделить пам€ть под структуру типа st_sample_password_info.\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    p_st_password_info->p_ch_password = f_str_input_dynamic(stdin, &p_st_password_info->i_password_length, NULL, PASSWORD_SIZE_STD);

    return p_st_password_info;
}

extern void f_st_pass_delete(struct st_sample_password_info * p_st_password_info)
{
    if (p_st_password_info->p_ch_password != NULL)
        free(p_st_password_info->p_ch_password);

    free(p_st_password_info);
}

