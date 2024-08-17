#include "input.h"
#include "input_static.h"

extern struct st_sample_file_info * f_file_info_create(void)
{
    auto struct st_sample_file_info * p_file_info = (struct st_sample_file_info *) malloc(sizeof(struct st_sample_file_info));

    if (p_file_info == NULL) {
        fprintf(stderr, "[%s, %d]: Failed to create file info.\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    p_file_info->_name = NULL;
    p_file_info->_ptr = NULL;
    p_file_info->_size = (unsigned long long int) 0;

    return p_file_info;
}

extern int f_file_open(struct st_sample_file_info * p_file)
{
    p_file->_ptr = fopen(p_file->_name, "rb+");

    if (p_file->_ptr == NULL) {
        return 1;
    }

    p_file->_size = f_file_size(p_file->_ptr);

    return 0;
}

extern char * f_str_input_dynamic(FILE const * p_file, int * const p_length, char const * const p_alphabeth, int const i_str_size_limit)
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
                i_str_size_max += BUFSIZ;

                if ((p_str = (char *) realloc(p_str, sizeof(char)*i_str_size_max)) == NULL) {
                    fprintf(stderr, "[FILE %s, LINE %d] Failed to increase size of string.\n", __FILE__, __LINE__);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    if (p_str_index == p_str) {
        free(p_str);
        return NULL;
    }
    else
        *p_str_index = '\0';


    if ((i_str_size_limit == 0) && i_str_size != i_str_size_max) {

        if ((p_str = (char *) realloc(p_str, sizeof(char)*i_str_size)) == NULL) {
            fprintf(stderr, "[FILE %s, LINE %d] Failed to decrease size of string.\n", __FILE__, __LINE__);
            exit(EXIT_FAILURE);
        }
    }


    if (p_length != NULL) {
        *p_length = --i_str_size;
    }


    return p_str;
}

extern char * f_str_search(FILE const * const p_file, char const * const p_alphabeth, char const * const p_str_searched)
{
    auto char * p_str_searched_index = p_str_searched;
    auto char * p_str_new = NULL;

    rewind(p_file);

    while (feof(p_file)==0) {
        if (*p_str_searched_index=='\0') {
            p_str_new = f_str_input_dynamic(p_file, NULL, p_alphabeth, 0);
            break;
        }
        else {
            if (*p_str_searched_index==fgetc(p_file)) {
                p_str_searched_index++;
            }
            else {
                p_str_searched_index = p_str_searched;
            }
        }
    }

    return p_str_new;
}

extern unsigned long long int f_file_size(FILE * p_file)
{
    auto unsigned long long int ulli_file_size = 0;

    rewind(p_file);

    while (feof(p_file)) {
        fgetc(p_file);
        ulli_file_size++;
    }

    return ulli_file_size;
}

extern inline void f_buffer_clear(FILE * p_stream)
{
    while (fgetc(stdin) != '\n')
        continue;
}
