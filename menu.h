#ifndef _MENU_H

#define STR_LEN 80
#define ALPHABET_SIZE 26
#define WORD_COLOR 100
#define GALLOW_COLOR 101
#define HANGMAN_COLOR 102
#define TIME_COLOR 103
#define MENU_COLOR 104
#define ARROW_DOWN 258
#define ARROW_UP 259
#define ARROW_LEFT 4
#define ARROW_RIGHT 5
#define SHIFT_LEFT -119
#define SHIFT_RIGHT -110
#define HIGHLIGHT_ALL 1
#define SPACE_KEY 32
#define ENTER_KEY 10
#define PAUSE_KEY 93
#define QUIT_KEY 27
#define CREDITS_KEY 47
#define VISIBILITY_KEY 47
#define BACKSPACE_KEY 7
#define TAB_KEY 9
#define MAXH 25
#define MAXW 80



int level;
int category;
int mode;
char levels[4][30];
char categories[7][20];




void InfoDisplay(char* _category, char* _level, int pvp);
void smallDisplay(char* text, int y, int _delay);
int getMenuIndexByID(int id);
int getMenuIndexByName(char* name);
int getMenuTotalItems(int id);
int getMenuTotalSubs(int id);
int getMenuTotal(int id);
void moveDown();
void moveUp();
void selectItem();
int menuDone();
void stringReset(char* string);
int easterEgg(char* _word, char* fill_in, char _inp_char);
void creditsDisplay();
void menuDisplay(int title_color);
int menu();


#define _MENU_H
#endif
