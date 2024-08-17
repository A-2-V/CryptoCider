#include <stdlib.h>
#include "input.h"
#include "menu.h"
#include "menu_static.h"

/***** EXTERN FUNCTIONS *****/

extern char ** f_menu_text_create(void)
{
    auto char ** p_arr_menu = NULL;

    p_arr_menu = (char **) malloc(sizeof(char *)*MENU_TEXT_ALL_POSITION);

    if (p_arr_menu == NULL) {
        fprintf(stderr, "[%s, %d] Failed to allocate memory for the menu.\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    MENU_ITEM_INIT(p_arr_menu, MENU_TEXT_START);
    MENU_ITEM_INIT(p_arr_menu, MENU_TEXT_INPUT);
    MENU_ITEM_INIT(p_arr_menu, MENU_TEXT_INPUT_REPEAT);
    MENU_ITEM_INIT(p_arr_menu, MENU_TEXT_TITLE1);
    MENU_ITEM_INIT(p_arr_menu, MENU_TEXT_YOUR_CHOICE);
    MENU_ITEM_INIT(p_arr_menu, MENU_TEXT_ENCRYPTION);
    MENU_ITEM_INIT(p_arr_menu, MENU_TEXT_DECRYPTION);
    MENU_ITEM_INIT(p_arr_menu, MENU_TEXT_SHOW_PASSWORD);
    MENU_ITEM_INIT(p_arr_menu, MENU_TEXT_QUIT);

    f_menu_text_reading(p_arr_menu);

    return p_arr_menu;
}

extern int f_menu_input_file(struct st_sample_file_info * p_file, char ** p_menu)
{
    puts(p_menu[MENU_TEXT_INPUT]);

    while (p_file->_ptr == NULL) {
        if ((p_file->_name = f_str_input_dynamic(p_file->_ptr, NULL, NULL, 0)) == NULL) {
                return 1;
        }

        if (f_file_open(p_file)) {
            free(p_file->_name);
            puts(p_menu[MENU_TEXT_INPUT_REPEAT]);
            continue;
        }
    }

    return 0;
}

extern int f_menu_choice_function(struct st_sample_file_info * p_file, char ** p_menu)
{
    /* Variables */
    auto char choice = 0;
    auto int menu_item_num = 1;

    puts(p_menu[MENU_TEXT_TITLE1]);

    for (enum en_sample_menu_text index = MENU_TEXT_ENCRYPTION; index<MENU_TEXT_QUIT; index++) {
        printf("%2d) %s\n", menu_item_num++, p_menu[index]);
    }

    printf("\n%2d) %s\n", 0, p_menu[MENU_TEXT_QUIT]);

    do {
        choice = fgetc(stdin);
        f_buffer_clear(stdin);

        switch (choice) {
            case '0':
                break;
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
        }
    } while (choice != '0');




    return 0;
}


/***** STATIC FUNCTIONS *****/

static void f_menu_text_reading(char ** p_menu_text)
{
    /* Variables */
    auto FILE * p_file_text = fopen(MENU_TEXT_FILE, "rb");
    auto char * p_str_readed = NULL;

    /* Checking the success of opening a file */
    if (p_file_text == NULL) {
        fprintf(stderr, "[%s, %d]: The file could not be opened.\n", __FILE__, __LINE__);
        return;
    }

    /* Search for a string */
    for (enum en_sample_menu_text en_index = MENU_TEXT_START;
                en_index < MENU_TEXT_ALL_POSITION;
                en_index++) {

        p_str_readed = f_str_search(p_file_text, MENU_ITEM_ALLOWED_SYMBOLS, p_menu_text[en_index]);
        if (p_str_readed != NULL) {
            p_menu_text[en_index] = p_str_readed;
        }
    }
}
