#ifndef _A2V_MENU_STATIC_H_
#define _A2V_MENU_STATIC_H_

/** REQUIRED HEADERS **/
#include <stdio.h>


/** CONSTANTS **/
#define MENU_TEXT_FILE "menu_text.txt"

#define MENU_ITEM_ALLOWED_SYMBOLS "abcdefghijklmnopqrstuvwxyz \
ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

#define MENU_ITEM_INIT(X,Y) X[Y] = #Y


/** PROTOTYPES **/
static void f_menu_text_reading(char ** p_menu_text);

#endif // _A2V_MENU_STATIC_H_
