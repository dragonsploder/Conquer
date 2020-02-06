#include "conquer.h"
#include <time.h>

GameFlags gameFlags;

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

// Set up terminal with ncurses library
void initNcurses(){
    // Init curses
    initscr(); 
    // Disable buffering and get one character-at-a-time input
    cbreak(); 
    // Get Special keys
    keypad(stdscr, TRUE);
    // Suppress echoing of typed keys
    noecho();
    // Hide cursor
    curs_set(0);
    initColor();

    nodelay(stdscr, true);
}

void initGame(){
    initrand();
    genMap(0.5, 4);
    printMap();
}


void placeRandCity(int owner){
    int y = 0;
    int x = 0;
    do{
        y = irand(MAP_HEIGHT);
        x = irand(MAP_WIDTH);
    } while(map[y][x].terrain != LAND && map[y][x].piece.id != CITY);
    placeCity(y, x,owner);
}


void gameLoop(){
    placeRandCity(PLAYER);
    placeRandCity(COMPUTER);

    gameFlags.turn = 0;
    while(true){
        gameFlags.turn++;
        for (int i = 0; i < SECONDS_BETWEEN_TURNS; i += 2){
            refresh();
            napms(2);
            printMap();
            doCommand(getch());
        }
        troopActions();
        printCurrentMoment();
    }
}

int main(){
    initNcurses();
    
    initGame();

    gameLoop();
    igetch();
    
    /*clear();
    int currentX = 0;
    int currentY = 0;
    int input = 0;
    while(input != 81){
        printView(currentY, currentX, VEIW_HEIGHT, VEIW_WIDTH);
        input = igetch();
        if (input == 'w' && currentY != 0){
            currentY--;
        } else if(input == 's' && currentY != MAP_HEIGHT - VEIW_HEIGHT){
            currentY++;
        } else if(input == 'a' && currentX != 0){
            currentX--;
        } else if(input == 'd' && currentX != MAP_WIDTH - VEIW_WIDTH){
            currentX++;
        }
    }*/

    // Reset terminal
    endwin();
}