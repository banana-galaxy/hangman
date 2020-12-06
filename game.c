/*************************************************************************/
/* Project: Hangman                                                      */
/* Authors: Alex Patrushin, April Ihly, William Hamilton                 */
/* Description: Group programming project for PCC CS133U C Programming   */
/*              class: Build a game. This is our take on the classic     */
/*              word puzzle game Hangman. We have added features not     */
/*              traditionally found in the paper-based game, such as a   */
/*              timer, difficulty levels and categories.                 */
/*************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include "hang.h"
#include "hang_words.h"
#include "credits.h"
#include "menu.h"


/*************************/
/* Initialize variables  */
/*************************/



/* Game Window */
void keywordDisplay(char* keyword, char* guess, int y) {
    int h, w;
    getmaxyx(stdscr, h, w);
    int wordLength = strlen(guess);

    int x = w/2-wordLength;

    move(h-1-y, x);

    // Display word puzzle
    for (int i = 0; i<wordLength; i++) {
        if ('A' <= keyword[i] && 'Z' >= keyword[i]) {
            attron(A_UNDERLINE); // turn on underline attribute
            addch(guess[i]); // display guess if it's a char from the alphabet
            attroff(A_UNDERLINE); // turn off underline attribute
        } else {
            addch(keyword[i]); // if not char from alphabet, display char
        }
        addch(' '); // set spacing for looks
    }
    refresh();
}

/* Display letter bank */
void alphabetDisplay(int* _colors, int y) {
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    int h, w;
    getmaxyx(stdscr, h, w);

    int startPosX = w/2-ALPHABET_SIZE;
    move(h-1-y, startPosX);

    // Display corresponding letter color based on 
    // no guess, right guess, wrong guess
    for (int i = 0; i<ALPHABET_SIZE; i++) {
        attron(COLOR_PAIR(_colors[i]));
        char letter = 'A'+i;
        addch(letter);
        attroff(COLOR_PAIR(_colors[i]));
        addch(' ');
    }
}

/* Determine if a letter has been guessed */
int findGuessed(char letter, int* _alphabet) {
    for (int i = 0; i<ALPHABET_SIZE; i++) {
        char alphabetChar = 'A'+i;

        // Determine if the letter pressed = the letter the array is on and
        // has not been guessed yet
        if (letter == alphabetChar && 0 != _alphabet[i]) {
            return 1;
        }
    }
    return 0;
}

/* Update color of letter in letter bank */
void updateAlphabet(int* _colors, char letter, int _found) {
    if (letter == -1) {
        return;
    }
    int index = letter - 'A';
    if (_found) {
        _colors[index] = 1;
    } else {
        _colors[index] = 2;
    }
}

/* If puzzle has non-alphabetic chars, auto-populate them in puzzle display */
void addNonAlpha(char* source, char* dest) {
    int length = strlen(source);
    for (int i = 0; i<length; i++) {
        if ('A' > source[i] || 'Z' < source[i]) {
            dest[i] = source[i];
        }
    }
}

/* Timer */
int timer = 0;
int startTime;
int nowTime;
int deltaTime = 0;
int timeLeft;
int preTime;
int timePause = 0;

/* Initiate timer functionality */
void timerInit(int _timer) {
    timer = _timer;
    startTime = time(0);
    nowTime = time(0);
    deltaTime = nowTime - startTime;
    timeLeft = timer - deltaTime;
    preTime = timeLeft;
}

/* Update timer if timer is not paused */
void timerUpdate(){
    if (0 == timePause) {
        nowTime = time(0);
        deltaTime = nowTime - startTime;
        timeLeft = timer - deltaTime;
    }
}

/* Redisplay timer if time left has changed */
int timeChange() {
    if (timeLeft != preTime) {
        preTime = timeLeft;
        return 1;
    } else {
        return 0;
    }
}

/* Reset timer if conditions met */
void timerReset() {
    startTime = time(0);
    timerUpdate();
}

/* Determine if no time left */
int timesUp(){
    if (0 >= timeLeft) {
        return 1;
    } else {
        return 0;
    }
}

/* Pause timer and update time variables when conditions met */
void timerPause(){
    nowTime = time(0);
    startTime = nowTime - deltaTime;
    timeLeft = timer - deltaTime;
    timePause = 1;
}

/* Resume timer when not paused */
void timerResume() {
    timePause = 0;
}

/* Set timer attributes and then display */
void timerDisplay(int y) {
    init_pair(5, COLOR_RED, COLOR_BLACK);
    int h, w;
    getmaxyx(stdscr, h, w);

    char strTime[STR_LEN];
    sprintf(strTime, "%d", timeLeft);

    int length = strlen(strTime);
    int x = w/2-length;
    
    if (timeLeft <= timer/10) {
        attron(COLOR_PAIR(5));
    }
    mvprintw(y, x, strTime);
    attroff(COLOR_PAIR(5));
    refresh();
}

/* Display end of game screen */
void endDisplay(char* phrase) {
    int h, w;
    getmaxyx(stdscr, h, w);

    int length = strlen(phrase);

    move(h/2, w/2-length/2);

    for (int i = 0; i<length; i++) {
        addch(phrase[i]);
        refresh();
        usleep(100000);
    }
    usleep(5000000);
}

int game(char* _category, char* _level, char* keyword, int gameTimer) {
    int h, w, preh, prew;
    getmaxyx(stdscr, h, w);
    preh = h;
    prew = w;
    int gamePaused = 0;
    uint k_len;
    char guessed[STR_LEN];
    char inp_char;
    int found = 0;
    int wrongCount = 0;
    int alphabetColors[ALPHABET_SIZE];

    int change = 1;
    k_len = strlen(keyword);
    memset(guessed, ' ', k_len); guessed[k_len] = 0;
    addNonAlpha(keyword, guessed);
    for (int i = 0; i<ALPHABET_SIZE; i++) {
        alphabetColors[i] = 0;
    }
    timerInit(gameTimer);

    while (1) {
        // update screen size variables
        getmaxyx(stdscr, h, w);

        // variable to track whether or not letter is found in the word
        found = 0;

        // input
        inp_char = getch();
        
        //Pause button 
        if (PAUSE_KEY == inp_char) {
            if (0 == gamePaused) {
                gamePaused = 1;
                clear();
                smallDisplay("Game Paused, press ] to resume", 0, 0);
                timerPause();
            } else {
                gamePaused = 0;
                timerResume();
                change = 1;
            }
        } else if (QUIT_KEY == inp_char) {
            return 1;
        }
        if (gamePaused) {
            timerPause();
            continue;
        }
        
        // if input is lowercase make uppercase
        if ('a' <= inp_char && 'z' >= inp_char) {
            inp_char = toupper(inp_char);
        } else if ('A' > inp_char || 'Z' < inp_char) {
            inp_char = -1;
        }

        // try to find input char in word, if found update everything accordingly
        if (0 == findGuessed(inp_char, alphabetColors)) {
            for (int i = 0; i < k_len; ++i) {
                if (inp_char == keyword[i] && -1 != inp_char) {       
                    change = 1;
                    found = 1;
                    guessed[i] = inp_char;
                    updateAlphabet(alphabetColors, inp_char, found);
                }
            }
        }

        // not found, update everything accordingly
        if (0 == found && -1 != inp_char) {
            if (0 == findGuessed(inp_char, alphabetColors)) {
                change = 1;
                wrongCount++;
                updateAlphabet(alphabetColors, inp_char, found);
                // hang him!
            }
        }

        // timer
        if (0 != gameTimer && 0 == timePause) {
            change = timeChange();
            timerUpdate();
            if (found) {
                timerReset();
            } else if (timesUp()) {
                timerReset();
                wrongCount++;
            }
        }

        // register window resize as a change
        if (preh != h || prew != w) {
            change = 1;
        }

        // draw everything out
        if (change) {
            clear();

            // check window size, and update timer accordingly
            if (w < MAXW && h < MAXH) {
                smallDisplay("Window too small, please resize.", 0, 0);
                timerPause();
                change = 0;
                continue;
            } else if (h < MAXH) {
                smallDisplay("Window height too small, please resize.", 0, 0);
                timerPause();
                change = 0;
                continue;
            } else if (w < MAXW) {
                smallDisplay("Window width too small, please resize.", 0, 0);
                timerPause();
                change = 0;
                continue;
            } else {
                timerResume();
            }

            InfoDisplay(_category, _level);

            init_color(COLOR_YELLOW, 580, 580, 580);
            init_color(COLOR_WHITE, 900, 900, 900);
            init_color(COLOR_CYAN, 419, 949, 921);
            init_color(COLOR_GREEN, 47, 788, 258);
            init_color(COLOR_RED, 929, 113, 54);
            init_pair(WORD_COLOR, COLOR_WHITE, COLOR_BLACK);
            init_pair(GALLOW_COLOR, COLOR_YELLOW, COLOR_BLACK);
            init_pair(HANGMAN_COLOR, COLOR_CYAN, COLOR_BLACK);
            init_pair(TIME_COLOR, COLOR_CYAN, COLOR_BLACK);
            int hangmanWidth = 20;
            int hangmanY = 3;
            int hangmanW = w/2-hangmanWidth/2;
            attron(COLOR_PAIR(GALLOW_COLOR));
            gallows(hangmanY, hangmanW);
            attron(COLOR_PAIR(HANGMAN_COLOR));
            switch (wrongCount)
            {
            case 1:
                wrong_guess_1(hangmanY, hangmanW);
                break;

            case 2:
                wrong_guess_2(hangmanY, hangmanW);
                break;

            case 3:
                wrong_guess_3(hangmanY, hangmanW);
                break;

            case 4:
                wrong_guess_4(hangmanY, hangmanW);
                break;

            case 5:
                wrong_guess_5(hangmanY, hangmanW);
                break;

            case 6:
                wrong_guess_6(hangmanY, hangmanW);
                break;
            
            default:
                break;
            }
            attroff(COLOR_PAIR(HANGMAN_COLOR));
            attron(COLOR_PAIR(WORD_COLOR));
            keywordDisplay(keyword, guessed, 3);
            attroff(COLOR_PAIR(WORD_COLOR));
            alphabetDisplay(alphabetColors, 1);
            if (0 != gameTimer) {
                attron(COLOR_PAIR(TIME_COLOR));
                timerDisplay(1);
                attroff(COLOR_PAIR(TIME_COLOR));
            }
            refresh();

            change = 0;
        }

        if (0 == strcmp(keyword, guessed)) {
            clear();
            usleep(4000000); // 4s
            srand(time(0));
            curs_set(1);
            smallDisplay("You won", h/2-2, 100000); // 100ms
            if (3 > wrongCount) {
                char chosenIndex = rand()%9;
                endDisplay(winEasy[rand()%winEasy_sz]);
            } else if (3 <= wrongCount && 4 >= wrongCount) {
                char chosenIndex = rand()%4;
                endDisplay(winMedium[rand()%winMedium_sz]);
            } else if (4 < wrongCount) {
                char chosenIndex = rand()%5;
                endDisplay(winHard[rand()%winHard_sz]);
            }
            curs_set(0);
            break;
        }
        if (6 <= wrongCount) {
            clear();
            usleep(2000000); // 2s
            srand(time(0));
            char chosenIndex = rand()%13;
            curs_set(1);
            char losingText[100] = "You lost, the chosen word was: ";
            strcat(losingText, keyword);
            smallDisplay(losingText, h/2-2, 100000); // 100ms
            endDisplay(gameOver[chosenIndex]);
            curs_set(0);
            break;
        }
        // update previous window size
        prew = w;
        preh = h;
    }
    return 0;
}


int main() {
    initscr();
    start_color();
    noecho();
    curs_set( 0 );
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    int stop = 0;

    while (!stop) {
        fflush(stdin);
        stop = menu();
        if (stop) {
            break;
        }

        int seconds;
        switch (level) {
            case 0:
                seconds = 0;
                break;

            case 1:
                seconds = 60*3;
                break;

            case 2:
                seconds = 60;
                break;

            case 3:
                seconds = 10;
                break;
        }

        char word[100] = "";
        srand(time(0));
        switch (category) {
            case 0:
                strcpy(word, anilib[rand()%anilib_sz]);
                break;

            case 1:
                strcpy(word, clib[rand()%clib_sz]);
                break;
            
            case 2:
                strcpy(word, countlib[rand()%countlib_sz]);
                break;

            case 3:
                strcpy(word, linglib[rand()%linglib_sz]);
                break;

            case 6:
                strcpy(word, capitalslib[rand()%capitalslib_sz]);
                break;
        }

        stop = game(categories[category], levels[level], word, seconds);
    }
    endwin();
        
}