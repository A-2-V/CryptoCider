#include "input.h"

extern char * f_str_input_dynamic(FILE const * p_file, int * const p_str_size, char const * const p_alphabeth, int const i_str_size_limit)
{
    auto char * p_str = NULL;
    auto char * p_str_index = NULL;

    auto int i_str_size = 0;
    auto int i_str_size_max;

    auto char * p_alphabeth_index;
    auto char ch_temp = 0;


    if (i_str_size_limit == 0) {
        i_str_size_max = A2V_str_standart_size;
    }
    else {
        i_str_size_max = i_str_size_limit;
    }


    if (p_file == NULL) {
        p_file = stdin;
    }


    if ((p_str = (char *) malloc(sizeof(char)*i_str_size_max)) == NULL) {
        fprintf(stderr, "[FILE %s, LINE %d] Failed to allocate memory for string.\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    p_str_index = p_str;


    while ((ch_temp = getc(p_file))) {
        if (ch_temp == '\n' || ch_temp == '\0' || ch_temp == EOF) {
            i_str_size++;
            break;
        }

        if (p_alphabeth != NULL) {
            p_alphabeth_index = p_alphabeth;

            while (*p_alphabeth_index != '\0') {
                if (*p_alphabeth_index == ch_temp)
                    break;
                else
                    p_alphabeth_index++;
            }

            if (*p_alphabeth_index == '\0')
                continue;
        }

        *p_str_index = ch_temp;

        p_str_index++;
        i_str_size++;

        if (i_str_size == i_str_size_max) {

            if (i_str_size_limit) {

                p_str_index--;

                while (getc(stdin) != '\n')
                    continue;

                break;
            }
            else {
                i_str_size_max += A2V_str_standart_size;

                if ((p_str = (char *) realloc(p_str, sizeof(char)*i_str_size_max)) == NULL) {
                    fprintf(stderr, "[FILE %s, LINE %d] Failed to increase size of string.\n", __FILE__, __LINE__);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    *p_str_index = '\0';


    if ((i_str_size_limit == 0) && i_str_size != i_str_size_max) {

        if ((p_str = (char *) realloc(p_str, sizeof(char)*i_str_size)) == NULL) {
            fprintf(stderr, "[FILE %s, LINE %d] Failed to decrease size of string.\n", __FILE__, __LINE__);
            exit(EXIT_FAILURE);
        }
    }


    if (p_str_size != NULL) {
        *p_str_size = i_str_size;
    }


    return p_str;
}

