#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include "menu.h"
#include "hang.h"

/* Menu selections */
int level = 0;
int category = 0;
int currentSelected = 0;
int menuIndex = 0;
int currentMenu = 1;
int play = 0;

/* Menus */
char menuNames[3][20] = {"Main Menu", "Difficulty", "Category"};
char mainMenu[3][20] = {"Play", "Difficulty", "Category"};
char levels[4][30] = {"Noob Gamer", "Casual Gamer", "Hardcore Gamer", 
                        "Nightmare lvl2020"};
char categories[7][20] = {"Animals", "C Libraries", "Countries", 
                            "Internet Lingo", "Long Words", "Programming", 
                            "US Capitals"};

struct Menu {
    char menuName[15];
    int menuId;
    int menuLvl;
    char items[9][20];
    int SubMenu[3];
};

struct Menu menus[] = {
    {.menuId = 1, .menuName = "Main Menu", .menuLvl = 1, 
        .items = {"Play", " "}, .SubMenu = {2, 3, 0}},
    {.menuId = 2, .menuName = "Difficulty", .menuLvl = 2,
        .items = {"Noob Gamer", "Casual Gamer", "Hardcore Gamer", 
                    "Nightmare lvl2020", " "}, .SubMenu = {0}},
    {.menuId = 3, .menuName = "Category", .menuLvl = 2, 
        .items = {"Animals", "C Libraries", "Countries", 
                    "Internet Lingo", "Long Words", "Programming", 
                    "US Capitals", " "}, .SubMenu = {0}},
    {.menuId = 0}
};

/************************/
/* Functions            */
/************************/

/* Display the user-chosen Category and Difficulty Level, and the 
   Quit/Pause/View Credits options in the game window */
void InfoDisplay(char* _category, char* _level){
    int h, w;
    getmaxyx(stdscr, h, w);
    if (0 == strcmp("\0", _category)){
        mvprintw(h-4, w-10, "quit: esc");
        mvprintw(h-2, w-11, "credits: /");
    } else {
        mvprintw(1, 1, _category);
        int length = strlen(_category);
        mvprintw(1, 3+length, _level);
        mvprintw(1, w-10, "quit: esc");
        mvprintw(1, w-20, "pause: ]");
    }
}

/* Display a message to the user if they resize the window too small
    Also adjusts the placement of the message,and the speed with which
    the message is 'typed out' on the screen                           */
void smallDisplay(char* text, int y, int _delay) {
    int h, w;
    getmaxyx(stdscr, h, w);
    int length = strlen(text);

    if (0 == _delay) {
        if (0 == y) {
            mvprintw(h/2, w/2-length/2, text);
        } else {
            mvprintw(y, w/2-length/2, text);
        }
    } else {
        if (0 == y) {
            move(h/2, w/2-length/2);
        } else {
            move(y, w/2-length/2);
        }
        for (int i = 0; i<length; i++) {
            addch(text[i]);
            refresh();
            usleep(_delay);
        }
    }
}

/* Gets the index of the menu as identified by 'menuID' in the menu struct */
int getMenuIndexByID(int id) {
    int i = 0;
    while (0 != menus[i].menuId) {
        if (menus[i].menuId == id) {
            return i;
        }
        i++;
    }
    return 0;
}

/* Gets the index of the menu as identified by 'menuName' in the menu struct */
int getMenuIndexByName(char* name) {
    int i = 0;
    while (0 != menus[i].menuId) {
        if (0 == strcmp(menus[i].menuName, name)) {
            return i;
        }
        i++;
    }
    return 0;
}

/* Gets the total unique items in each menu as defined in the menu struct */
int getMenuTotalItems(int id) {
    int index = getMenuIndexByID(id);
    int i = 0;
    while (0 != strcmp(" ", menus[index].items[i])) {
        i++;
    }
    return i;
}

/* Gets the total submenus available under each menu as defined in the menu struct */
int getMenuTotalSubs(int id) {
    int index = getMenuIndexByID(id);
    int i = 0;
    while (0 != menus[index].SubMenu[i]) {
        i++;
    }
    return i;
}

/* Sums the two previous functions to get everything a menu contains */
int getMenuTotal(int id) {
    return getMenuTotalItems(id) + getMenuTotalSubs(id);
}

/* Move the cursor down the menu */
void moveDown() {
    int max = getMenuTotal(currentMenu)-1;
    if (menuIndex < max) {
        menuIndex++;
    }
}

/* Move the cursor up the menu */
void moveUp() {
    if (0 < menuIndex) {
        menuIndex--;
    }
}

/* Select the corresponding menu choice based on cursor position */
void selectItem() {
    int TotalItems = getMenuTotalItems(currentMenu);

    // If no difficulty or category chosen, default to 1st level of each
    if (menuIndex < TotalItems) {
        switch (currentMenu) {
            case 1:
                play = 1;
                break;
            case 2:
                level = menuIndex;
                break;
            case 3:
                category = menuIndex;
                break;
        }
        currentMenu = 1;
    } else {
        switch (menuIndex) {
            case 1:
                currentMenu = 2;
                break;

            case 2:
                currentMenu = 3;
                break;
        }
    }
    menuIndex = 0;
}

/* When finished choosing level or category, game is ready to play */
int menuDone() {
    return play;
}

/* Empty a string of all its contents, for the Easter Egg */
void stringReset(char* string) {
    int i = 0;
    while ('\0' != string[i]) {
        string[i] = '\0';
        i++;
    }
}

/* Set up hidden Easter Egg */
int easterEgg(char* _word, char* fill_in, char _inp_char) {
    int length = strlen(_word);
    int amountCompleted = 0;
    for (int i = 0; i<length; i++) {
        if (_word[i] == fill_in[i]) {
            amountCompleted++;
        } else {
            break;
        }
    }

    if (_word[amountCompleted] == _inp_char) {
        fill_in[amountCompleted] = _inp_char;
        beep();
    }
    
    if (0 == strcmp(_word, fill_in)) {
        stringReset(fill_in);
        return 1;
    }
    return 0;
}

/* Display all elements of the main menu */
void menuDisplay(int title_color) {
    char instructions[2][50] = {"Use Up and Down arrow keys to navigate", 
                                    "Press Space to select"};
    int h, w;
    getmaxyx(stdscr, h, w);

    game_title(title_color);

    // Set color attributes for menu
    init_color(COLOR_GREEN, 47, 788, 258);
    init_pair(MENU_COLOR, COLOR_GREEN, COLOR_BLACK);

    // Turn color attribute on
    attron(COLOR_PAIR(MENU_COLOR));

    // Display name of current menu
    int y = 9;
    char menuName[20];
    strcpy(menuName, menuNames[currentMenu-1]);
    mvprintw(y, w/2-strlen(menuName)/2, menuName);
    y++;

    // Display menu instructions
    for (int i = 0; i<2; i++){
        int instructionLength = strlen(instructions[i]);
        mvprintw(y, w/2-instructionLength/2, instructions[i]);
        y++;
    }

    y++;
    
    // Display all the menu options of the current specific menu
    for (int j = 0; j<getMenuTotal(currentMenu); j++) {
        
        if (menuIndex == j) {
            mvprintw(y, w/2-4, "> "); // display arrow at cursor pos in menu
        } else {
            mvprintw(y, w/2-4, "  "); // don't display arrow anywhere else
        }
        
        if (2 == currentMenu) {
            currentSelected = level; // set difficulty to selection
        } else if (3 == currentMenu) {
            currentSelected = category; // set category to selection
        }

        if (j < getMenuTotalItems(currentMenu)) {
            if (currentSelected == j && 1 != currentMenu){
                attron(A_BOLD); // turn on bold attribute
            }
            printw(menus[currentMenu-1].items[j]); 
            attroff(A_BOLD); // turn off bold attribute
        } else {
            int menuI = j - getMenuTotalItems(currentMenu) + 1;
            
            if (1 != menus[menuI].menuLvl) { // checks if menu is top- or sub-lvl
                printw(menus[menuI].menuName); // print submenus
            }
            
        }
        
        y++;
    }

    // turn color attribute off
    attroff(COLOR_PAIR(MENU_COLOR));

    // update terminal window
    refresh();
}

/* Menu Window */
int menu() {
    int inp_char;
    int _change = 1;
    int h, w, preh, prew;
    getmaxyx(stdscr, h, w);
    prew = w;
    preh = h;
    level = 0;
    category = 0;
    currentSelected = 0;
    menuIndex = 0;
    play = 0;
    char easter[] = "hangman";
    char easterFillIn[8] = "";
    int easterBlink = 0;
    int creditsToggle = 0;
    

    while (1) {
        getmaxyx(stdscr, h, w);
        inp_char = getch();

        // Display easter egg if conditions met
        easterBlink = easterEgg(easter, easterFillIn, inp_char);

        // Determines if Easter Egg should blink when displayed 
        if (easterBlink) {
            _change = 1;  
        }

        // Toggle to display credits screen 
        if (CREDITS_KEY == inp_char) {
            if (creditsToggle) {
                creditsToggle = 0;
            } else {
                creditsToggle = 1;
            }
            _change = 1;
        } else if (QUIT_KEY == inp_char) { // end program
                return 1;
        }

        // Set arrow keys as navigation and space key as selector 
        // when not in the credits screen
        if (!creditsToggle) {
            if (ARROW_DOWN == inp_char){
                moveDown();
                _change = 1;
            } else if (ARROW_UP == inp_char) {
                moveUp();
                _change = 1;
            } else if (SPACE_KEY == inp_char) {
                selectItem();
                _change = 1;
            }
        }

        // leave menu and enter game
        if (menuDone()) {
            break;
        }

        // Watches for window size. If window size =/= previous window size,
        // adjust display
        if (prew != w || preh != h) {
            _change = 1;
        }

        // Update display if anything currently displayed changes
        if (_change) {
            clear();

            // Stop display, warn user if window size too small
            if (w < MAXW && h < MAXH) {
                smallDisplay("Window too small, please resize.", 0, 0);
                continue;
            } else if (h < MAXH) {
                smallDisplay("Window height too small, please resize.", 0, 0);
                continue;
            } else if (w < MAXW) {
                smallDisplay("Window width too small, please resize.", 0, 0);
                continue;
            }

            InfoDisplay("\0", "\0");
            
            if (!creditsToggle) {
                if (easterBlink) { // set color scheme of Easter Egg if on
                    menuDisplay(COLOR_WHITE);
                    usleep(150000);
                    menuDisplay(COLOR_RED);
                    usleep(150000);
                    menuDisplay(COLOR_YELLOW);
                    usleep(150000);
                    menuDisplay(COLOR_GREEN);
                    usleep(150000);
                    menuDisplay(COLOR_BLUE);
                    usleep(150000);
                    easterBlink = 0;
                }
                menuDisplay(COLOR_MAGENTA); // set color if Easter Egg not on
            } else {
                creditsDisplay();
            }

            _change = 0;
        }
        preh = h;
        prew = w;
    }
    return 0;

}