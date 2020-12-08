/*************************************************************************/
/* Project: Hangman                                                      */
/* Date: 12/7/2020                                                       */
/* Authors: Alex Patrushin, April Ihly, William Hamilton                 */
/* Description: Group programming project for PCC CS133U C Programming   */
/*              class: Build a game. This is our take on the classic     */
/*              word puzzle game Hangman. We have added features not     */
/*              traditionally found in the paper-based game, such as a   */
/*              timer, difficulty levels and categories.                 */
/* Build: gcc game.c credits.c hang.c menu.c -o hangman.exe -lncurses    */
/* Run: ./hangman.exe                                                    */
/*************************************************************************/

#include <string.h>
#include <ncurses.h>


/* Display Game Title */
void game_title(int foreground_color) {
    int h, w;
    getmaxyx(stdscr, h, w);
  
    init_pair(80, foreground_color, COLOR_BLACK);
    attron(COLOR_PAIR(80));
  
    int x = w/2-34;
    int y = 1;
  
    mvprintw(y,  x, "H    H     A     N      N    GGGGG   M M     M M     A  "
    "   N      N");
    mvprintw(y+1, x, "H    H   A   A   N N    N   G     G  M  M   M  M   A   A"
    "   N N    N");
    mvprintw(y+2, x, "H    H  A     A  N  N   N   G        M   M M   M  A     "
    "A  N  N   N");
    mvprintw(y+3, x, "HHHHHH  AAAAAAA  N   N  N   G   GGG  M    M    M  AAAAAA"
    "A  N   N  N");
    mvprintw(y+4, x, "H    H  A     A  N    N N   G     G  M         M  A     "
    "A  N    N N");
    mvprintw(y+5, x, "H    H  A     A  N     NN   G     G  M         M  A     "
    "A  N     NN");
    mvprintw(y+6, x, "H    H  A     A  N      N    GGGGG   M         M  A     "
    "A  N      N");
    attroff(COLOR_PAIR(80));
    refresh();

}

/* Display Gallows */
void gallows(int y, int x) {

    mvprintw(y,    x, "        ___________");
    mvprintw(y+1,  x, "       |   ______  |");
    mvprintw(y+2,  x, "       |  |      | |");
    mvprintw(y+3,  x, "       |  |      |_|");
    mvprintw(y+4,  x, "       |  |");
    mvprintw(y+5,  x, "       |  |");
    mvprintw(y+6,  x, "       |  |");
    mvprintw(y+7,  x, "       |  |");
    mvprintw(y+8,  x, "       |  |");
    mvprintw(y+9,  x, "       |  |");
    mvprintw(y+10, x, "       |  |");
    mvprintw(y+11, x, "       |  |");
    mvprintw(y+12, x, "       |  |");
    mvprintw(y+13, x, " ______|  |______");
    mvprintw(y+14, x, "|                |");
    mvprintw(y+15, x, "|________________|");

}

const int hm_offset_y = 4;
const int hm_offset_x = 15;

/* Display Head only */
void wrong_guess_1(int y, int x) {
    x += hm_offset_x;
    y += hm_offset_y;
    mvprintw(y,   x, "  ***");
    mvprintw(y+1, x, " *   *");
    mvprintw(y+2, x, "  ***");
}

/* Display Head/Torso */
void wrong_guess_2(int y, int x) {
    x += hm_offset_x;
    y += hm_offset_y;
    mvprintw(y,   x, "  ***");
    mvprintw(y+1, x, " *   *");
    mvprintw(y+2, x, "  ***");
    mvprintw(y+3, x, "   |  ");
    mvprintw(y+4, x, "   |  ");
    mvprintw(y+5, x, "   |  ");
}

/* Display Left arm */
void wrong_guess_3(int y, int x) {
    x += hm_offset_x;
    y += hm_offset_y;
    mvprintw(y,   x, "  ***");
    mvprintw(y+1, x, " *   *");
    mvprintw(y+2, x, "  ***");
    mvprintw(y+3, x, "___|  ");
    mvprintw(y+4, x, "   |  ");
    mvprintw(y+5, x, "   |  ");
}

/* Display Right arm */
void wrong_guess_4(int y, int x) {
    x += hm_offset_x;
    y += hm_offset_y;
    mvprintw(y,   x, "  ***");
    mvprintw(y+1, x, " *   *");
    mvprintw(y+2, x, "  ***");
    mvprintw(y+3, x, "___|___");
    mvprintw(y+4, x, "   |   ");
    mvprintw(y+5, x, "   |   ");
}

/* Display Left leg */
void wrong_guess_5(int y, int x) {
    x += hm_offset_x;
    y += hm_offset_y;
    mvprintw(y,   x, "  ***");
    mvprintw(y+1, x, " *   *");
    mvprintw(y+2, x, "  ***");
    mvprintw(y+3, x, "___|___");
    mvprintw(y+4, x, "   |   ");
    mvprintw(y+5, x, "   |   ");
    mvprintw(y+6, x, "  /    ");
    mvprintw(y+7, x, " /     ");
}

/* Display Right leg */
  void wrong_guess_6(int y, int x) {
    x += hm_offset_x;
    y += hm_offset_y;
    mvprintw(y,   x, "  ***");
    mvprintw(y+1, x, " *   *");
    mvprintw(y+2, x, "  ***");
    mvprintw(y+3, x, "___|___");
    mvprintw(y+4, x, "   |   ");
    mvprintw(y+5, x, "   |   ");
    mvprintw(y+6, x, "  / \\  ");
    mvprintw(y+7, x, " /   \\ ");
}
