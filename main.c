#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "crypto.h"
#include "menu.h"

#define CHANGE_CODEPAGE system("chcp 1251")
#define CLEAR_SCREEN system("cls")

struct st_sample_text_menu_info * p_st_menu_info;

int main(int argc, char * argv[])
{
    /* Variables */
    auto char ** p_menu = NULL;
    auto struct st_sample_file_info * p_file = f_file_info_create();

    /* Set code page */
    CHANGE_CODEPAGE;
    CLEAR_SCREEN;

    /* Creating a menu */
    p_menu = f_menu_text_create();

    /* Dispaying starting message */
    puts(p_menu[MENU_TEXT_START]);


    if (argc == 1) {
        while (f_menu_input_file(p_file, p_menu) == 0) {
           f_menu_choice_function(p_file, p_menu);
        }
    }
    else {
        for (int arg_index=0; arg_index<argc; arg_index++) {
            p_file->_name = argv[arg_index];
            if (f_file_open(p_file))
                continue;
        }
    }

    puts(p_menu[MENU_TEXT_QUIT]);

    return 0;
}
