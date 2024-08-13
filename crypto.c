#include <stdio.h>
#include <stdlib.h>
#include "crypto.h"

/***���������***/
extern struct st_sample_password_info * f_st_pass_create(void);
extern char * f_str_input_dynamic(FILE const * const p_file, int * const p_length, char const * const p_alphabeth, int const i_str_size_limit);



/**����������**/
extern struct st_sample_password_info * f_st_pass_create(void)
{
    auto struct st_sample_password_info * p_st_password_info = (struct st_sample_password_info *) malloc(sizeof(struct st_sample_password_info));

    if (p_st_password_info == NULL) {
        fputs("�� ������� �������� ������ ��� ��������� ���� st_sample_password_info", stderr);
        exit(EXIT_FAILURE);
    }

    p_st_password_info->p_ch_password = f_str_input_dynamic(stdin, &p_st_password_info->i_password_length, NULL, PASSWORD_SIZE_STD);
}


extern char * f_str_input_dynamic(FILE const * const p_file, int * const p_length, char const * const p_alphabeth, int const i_str_size_limit)
{
    /** ���������� ���������� **/
    auto char * p_str = NULL; /* ������ */
    auto char * p_str_index = NULL; /* �������� �� ������ */

    auto int i_str_size = 0; /* ������� ������ ������ */
    auto int i_str_size_max; /* ���������� ������ ������ */

    auto char * p_alphabeth_index;
    auto char ch_temp = 0; /* ��������� ������ */


    /** ��������� ������������� ������� ������ **/
    if (i_str_size_limit == 0) {
        i_str_size_max = A2V_str_standart_size; /* ����������� ������ */
    }
    else {
        i_str_size_max = i_str_size_limit; /* �������� ������ */
    }


    /** ��������� ������ ��� ������ **/
    if ((p_str = (char *) malloc(sizeof(char)*i_str_size_max)) == NULL) {
        fprintf(stderr, "[%d] �� ������� �������� ������ ��� ������.\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    /* ��������� ������� � ������ ������ */
    p_str_index = p_str;


    /** ������������ ����������� � ������ **/
    while ((ch_temp = getc(p_file))) {

        /* ��������� ����� ������ */
        if (ch_temp == '\n' || ch_temp == '\0' || ch_temp == EOF) {

            i_str_size++;

            break;
        }

        /* ��� ������� ��������� �������� */
        if (p_alphabeth != NULL) {

            /* ��������� "�������" �� �������� */
            p_alphabeth_index = p_alphabeth;

            /* ����� ���������� ������� � �������� */
            while (*p_alphabeth_index != '\0') {
                if (*p_alphabeth_index == ch_temp)
                    break;
                else
                    p_alphabeth_index++;
            }

            /* ��� ���������� -- ���� ���������� ������� */
            if (*p_alphabeth_index == '\0')
                continue;
        }

        /* ����������� �������� � ������ */
        *p_str_index = ch_temp;

        p_str_index++;
        i_str_size++;

        /* �������� ������������� ������� ������*/
        if (i_str_size == i_str_size_max) {

            /* ���� ���������� ���������� ������ ������ */
            if (i_str_size_limit) {

                *p_str_index--;

                while (getc(stdin) != '\n')
                    continue;

                break;
            }
            else {
                /* ��������� ������������� ������� ������ */
                i_str_size_max += A2V_str_standart_size;

                /* ���������� ���������� ������ */
                if ((p_str = (char *) realloc(p_str, sizeof(char)*i_str_size_max)) == NULL) {
                    fprintf(stderr, "[%d] �� ������� ��������� ������ ������.\n", __LINE__);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    /* ��������� ������� ����� ������ */
    *p_str_index = '\0';


    /** ������������ �������� ����� ���������� ������ (��� �������) **/
    if ((i_str_size_limit == 0) && i_str_size != i_str_size_max) {

        if ((p_str = (char *) realloc(p_str, sizeof(char)*i_str_size)) == NULL) {
            fprintf(stderr, "[%d] �� ������� ��������� ������ ������.\n", __LINE__);
            exit(EXIT_FAILURE);
        }
    }


    /** �������� ����� ������ **/
    if (p_length != NULL) {
        *p_length = i_str_size;
    }


    /** ������� ��������� �� ������ ������ **/
    return p_str;
}
