#include "conquer.h"


// Set up terminal with ncurses library
void initNcurses(){
    // Init curses
    initscr(); 
    // Disable buffering and get one character-at-a-time input
    cbreak(); 
    // Suppress echoing of typed keys
    noecho();
    // Hide cursor
    curs_set(0);
}

void initColor(){
    // Alow the use of color
    use_default_colors();
    start_color();
    init_pair(COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
}

void initGame(){
    genMap(0.5, 4);
    //printMap();
}

int main(){
    initNcurses();
    initColor();
    
    initGame();
    getch();
    clear();
    int currentX = 0;
    int currentY = 0;
    int input = 0;
    while(input != 81){
        printVeiw(currentY, currentX, 20, 80);
        input = getch();
        if (input == 'w' && currentY != 0){
            currentY--;
        } else if(input == 's' && currentY != MAP_HEIGHT - VEIW_HEIGHT){
            currentY++;
        } else if(input == 'a' && currentX != 0){
            currentX--;
        } else if(input == 'd' && currentX != MAP_WIDTH - VEIW_WIDTH){
            currentX++;
        }
    }

    // Reset terminal
    endwin();
}