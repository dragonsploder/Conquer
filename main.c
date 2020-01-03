#include "conquer.h"

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
}

void initGame(){
    initrand();
    genMap(0.5, 4);
    printMap();
}


void justify(){
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        if (map[i][j].piece.id == CITY){
            map[i][j].piece.newPlayerTroops+=TROOPS_PER_TURN;
        }
    )
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        if (map[i][j].terrain == LAND && map[i][j].piece.playerTroops > 0){
            for (int c = 0; c < 9; c++){
                int troopsToMove = irand(map[i][j].piece.playerTroops);
                /*
                Piece *moveCity = &map[i + (irand(3) - 1)][j + (irand(3) - 1)].piece;
                if(moveCity->playerTroops + troopsToMove <= MAX_TROOPS_IN_TILE){
                    moveCity->newPlayerTroops += troopsToMove;
                    map[i][j].piece.playerTroops -= troopsToMove;
                }*/
                //Location offset = {(irand(3) - 1), (irand(3) - 1)};
                Location cityOffset;
                cityOffset.y = (irand(3) - 1);
                cityOffset.x = (irand(3) - 1);
                if (map[i + cityOffset.y][j + cityOffset.x].terrain == LAND && map[i + cityOffset.y][j + cityOffset.x].piece.playerTroops + troopsToMove <= MAX_TROOPS_IN_TILE){
                    map[i + cityOffset.y][j + cityOffset.x].piece.newPlayerTroops += troopsToMove;
                    map[i][j].piece.playerTroops -= troopsToMove;
                }
            }
        }
    )
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        map[i][j].piece.playerTroops += map[i][j].piece.newPlayerTroops;
        map[i][j].piece.newPlayerTroops = 0;
        if (map[i][j].piece.playerTroops > MAX_TROOPS_IN_TILE){
            map[i][j].piece.playerTroops = MAX_TROOPS_IN_TILE;
        }
    )
}

void gameLoop(){
    map[irand(MAP_HEIGHT)][irand(MAP_WIDTH)].piece = pieceTypes[CITY];
    while(true){
        //doCommand();
        getch();
        justify();
        printMap();
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