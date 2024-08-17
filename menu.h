#ifndef _A2V_MENU_H_
#define _A2V_MENU_H_

extern enum en_sample_menu_text {
    MENU_TEXT_START,
    MENU_TEXT_INPUT,
    MENU_TEXT_INPUT_REPEAT,
    MENU_TEXT_TITLE1,
    MENU_TEXT_YOUR_CHOICE,

    /* FUNCTIONS */
    MENU_TEXT_ENCRYPTION,
    MENU_TEXT_DECRYPTION,
    MENU_TEXT_SHOW_PASSWORD,
    MENU_TEXT_QUIT,

    MENU_TEXT_ALL_POSITION
};

extern char ** f_menu_text_create(void);
extern int f_menu_input_file(struct st_sample_file_info * p_file, char ** p_menu);
extern int f_menu_choice_function(struct st_sample_file_info * p_file, char ** p_menu);


#endif // _A2V_MENU_H_
