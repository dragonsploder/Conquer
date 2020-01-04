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
        Piece *currentPiece = &map[i][j].piece;
        if (currentPiece->id == CITY){
            if (currentPiece->owner == PLAYER){
                currentPiece->newPlayerTroops+=TROOPS_PER_TURN;
            } else if (map[i][j].piece.owner == COMPUTER){
                currentPiece->newComputerTroops+=TROOPS_PER_TURN;
            }
        }
    )
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        if (map[i][j].terrain == LAND){
            Piece *currentPiece = &map[i][j].piece;
            for (int c = 0; c < 9; c++){
                if (currentPiece->playerTroops <= MIN_TROOP_MOVE){
                    break;
                }
                int troopsToMove = irand(currentPiece->playerTroops - MIN_TROOP_MOVE) + MIN_TROOP_MOVE;
                Location cityOffset;
                cityOffset.y = (irand(3) - 1);
                cityOffset.x = (irand(3) - 1);
                if (map[i + cityOffset.y][j + cityOffset.x].terrain == LAND && map[i + cityOffset.y][j + cityOffset.x].piece.playerTroops + troopsToMove <= MAX_TROOPS_IN_TILE){
                    map[i + cityOffset.y][j + cityOffset.x].piece.newPlayerTroops += troopsToMove;
                    currentPiece->playerTroops -= troopsToMove;
                }
            }
            for (int c = 0; c < 9; c++){
                if (currentPiece->computerTroops <= MIN_TROOP_MOVE){
                    break;
                }
                int troopsToMove = irand(currentPiece->computerTroops - MIN_TROOP_MOVE) + MIN_TROOP_MOVE;
                Location cityOffset;
                cityOffset.y = (irand(3) - 1);
                cityOffset.x = (irand(3) - 1);
                if (map[i + cityOffset.y][j + cityOffset.x].terrain == LAND && map[i + cityOffset.y][j + cityOffset.x].piece.computerTroops + troopsToMove <= MAX_TROOPS_IN_TILE){
                    map[i + cityOffset.y][j + cityOffset.x].piece.newComputerTroops += troopsToMove;
                    currentPiece->computerTroops -= troopsToMove;
                }
            }
        }
    )
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        Piece *currentPiece = &map[i][j].piece;

        if (currentPiece->playerTroops > currentPiece->computerTroops){
            currentPiece->playerTroops -= currentPiece->computerTroops;
        } else {
            currentPiece->computerTroops -= currentPiece->playerTroops;
        }

        if (currentPiece->id == CITY){
            if (currentPiece->owner == PLAYER && currentPiece->playerTroops < currentPiece->computerTroops){
                currentPiece->owner = COMPUTER;
            } else if (currentPiece->owner == COMPUTER && currentPiece->computerTroops < currentPiece->playerTroops){
                currentPiece->owner = PLAYER;
            }
        }
    )
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        Piece *currentPiece = &map[i][j].piece;

        currentPiece->playerTroops += currentPiece->newPlayerTroops;
        currentPiece->newPlayerTroops = 0;
        if (currentPiece->playerTroops > MAX_TROOPS_IN_TILE){
            currentPiece->playerTroops = MAX_TROOPS_IN_TILE;
        }


        if (currentPiece->computerTroops > MAX_TROOPS_IN_TILE){
            currentPiece->computerTroops = MAX_TROOPS_IN_TILE;
        }
        currentPiece->computerTroops += currentPiece->newComputerTroops;
        currentPiece->newComputerTroops = 0;
    )
}

void gameLoop(){
    int y = irand(MAP_HEIGHT);
    int x = irand(MAP_WIDTH);
    map[y][x].piece = pieceTypes[CITY];
    map[y][x].piece.owner = PLAYER;

    map[y][x+3].piece = pieceTypes[CITY];
    map[y][x+3].piece.owner = PLAYER;

    map[y+5][x].piece = pieceTypes[CITY];
    map[y+5][x].piece.owner = COMPUTER;

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