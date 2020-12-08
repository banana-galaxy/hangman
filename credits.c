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

#include <ncurses.h>

/* Display the credits */
void creditsDisplay() {
    char credits[][62] = {"Thanks to https://bit.ly/39zOnLJ",
                        "Thanks to https://bit.ly/3lyKSHu",
                        "Thanks to https://bit.ly/2Vu5lmq",
                        "Thanks to https://bit.ly/3mLMgIB",
                        "Thanks to https://bit.ly/3lsjoDy",
                        "Thanks to https://bit.ly/33FT82C",
                        "Thanks to https://bit.ly/37zTYPE",
                        "Thanks to https://bit.ly/39AkLha",
                        "",
                        "Made by William Hamilton, April Ihly,"
                        " and Alexander Patrushin"};

    char whyCredits[][72] = {"for introducing us to ncurses",
                        "for providing us with a comprehensive guide"
                        " on ncurses",
                        "for pointing out a way to take input from"
                        " unusual keyboard keys",
                        "for helping with program compilation details",
                        "for providing an ncurses menu example",
                        "for helping realize that attributes in ncurses"
                        " are like toggle switches",
                        "for introducing us to ncurses colors",
                        "for telling a way to clear the input buffer"};


    int h, w;
    getmaxyx(stdscr, h, w);

    // Determines length of string to auto-adjust array size
    size_t credits_sz = sizeof(credits) / sizeof(credits[0]);
    size_t whyCredits_sz = sizeof(whyCredits) / sizeof(whyCredits[0]);

    credits_sz;
    int y = 2;

    // specify location of string in window based on string length
    // and print to window
    for (int i = 0; i<credits_sz; i++) {
        mvprintw(y, 3, credits[i]);
        if (i < whyCredits_sz){
            y++;
            mvprintw(y, 6, whyCredits[i]);
        }
        y++;
    }

}