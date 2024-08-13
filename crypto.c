#include <stdio.h>
#include <stdlib.h>
#include "crypto.h"

/***ПРОТОТИПЫ***/
extern struct st_sample_password_info * f_st_pass_create(void);
extern char * f_str_input_dynamic(FILE const * const p_file, int * const p_length, char const * const p_alphabeth, int const i_str_size_limit);



/**РЕАЛИЗАЦИЯ**/
extern struct st_sample_password_info * f_st_pass_create(void)
{
    auto struct st_sample_password_info * p_st_password_info = (struct st_sample_password_info *) malloc(sizeof(struct st_sample_password_info));

    if (p_st_password_info == NULL) {
        fputs("Не удалось выделить память под структуру типа st_sample_password_info", stderr);
        exit(EXIT_FAILURE);
    }

    p_st_password_info->p_ch_password = f_str_input_dynamic(stdin, &p_st_password_info->i_password_length, NULL, PASSWORD_SIZE_STD);
}


extern char * f_str_input_dynamic(FILE const * const p_file, int * const p_length, char const * const p_alphabeth, int const i_str_size_limit)
{
    /** ОБЪЯВЛЕНИЕ ПЕРЕМЕННЫХ **/
    auto char * p_str = NULL; /* строка */
    auto char * p_str_index = NULL; /* движение по строке */

    auto int i_str_size = 0; /* текущий размер строки */
    auto int i_str_size_max; /* предельный размер строки */

    auto char * p_alphabeth_index;
    auto char ch_temp = 0; /* считанный символ */


    /** УСТАНОВКА МАКСИМАЛЬНОГО РАЗМЕРА СТРОКИ **/
    if (i_str_size_limit == 0) {
        i_str_size_max = A2V_str_standart_size; /* стандартный размер */
    }
    else {
        i_str_size_max = i_str_size_limit; /* заданный размер */
    }


    /** ВЫДЕЛЕНИЕ ПАМЯТИ ПОД СТРОКУ **/
    if ((p_str = (char *) malloc(sizeof(char)*i_str_size_max)) == NULL) {
        fprintf(stderr, "[%d] Не удалось выделить память под строку.\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    /* Установка индекса в начало строки */
    p_str_index = p_str;


    /** ПОСИМВОЛЬНОЕ КОПИРОВАНИЕ В СТРОКУ **/
    while ((ch_temp = getc(p_file))) {

        /* Выявление конца строки */
        if (ch_temp == '\n' || ch_temp == '\0' || ch_temp == EOF) {

            i_str_size++;

            break;
        }

        /* При наличии заданного алфавита */
        if (p_alphabeth != NULL) {

            /* Установка "бегунка" по алфавиту */
            p_alphabeth_index = p_alphabeth;

            /* Поиск введенного символа в алфавите */
            while (*p_alphabeth_index != '\0') {
                if (*p_alphabeth_index == ch_temp)
                    break;
                else
                    p_alphabeth_index++;
            }

            /* При отсутствии -- ввод следующего символа */
            if (*p_alphabeth_index == '\0')
                continue;
        }

        /* Копирование символов в строку */
        *p_str_index = ch_temp;

        p_str_index++;
        i_str_size++;

        /* Проверка достаточности размера строки*/
        if (i_str_size == i_str_size_max) {

            /* Если установлен конкретный размер строки */
            if (i_str_size_limit) {

                *p_str_index--;

                while (getc(stdin) != '\n')
                    continue;

                break;
            }
            else {
                /* Повышение максимального размера строки */
                i_str_size_max += A2V_str_standart_size;

                /* Расширение выделенной строки */
                if ((p_str = (char *) realloc(p_str, sizeof(char)*i_str_size_max)) == NULL) {
                    fprintf(stderr, "[%d] Не удалось увеличить размер строки.\n", __LINE__);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    /* Установка символа конца строки */
    *p_str_index = '\0';


    /** ОСВОБОЖДЕНИЕ ИЗЛИШНЕЙ ЧАСТИ ВЫДЕЛЕННОЙ ПАМЯТИ (ПРИ НАЛИЧИИ) **/
    if ((i_str_size_limit == 0) && i_str_size != i_str_size_max) {

        if ((p_str = (char *) realloc(p_str, sizeof(char)*i_str_size)) == NULL) {
            fprintf(stderr, "[%d] Не удалось сократить размер строки.\n", __LINE__);
            exit(EXIT_FAILURE);
        }
    }


    /** ПЕРЕДАЧА ДЛИНЫ СТРОКИ **/
    if (p_length != NULL) {
        *p_length = i_str_size;
    }


    /** ВОЗВРАТ УКАЗАТЕЛЯ НА НАЧАЛО СТРОКИ **/
    return p_str;
}
