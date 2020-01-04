#include <ncurses.h>


#ifndef KING_H
#define KING_H

#define KEY_ENTER 10

#define PLAYER_COLOR COLOR_CYAN
#define COMPUTER_COLOR COLOR_RED

#define TROOPS_PER_TURN 50

#define MAX_TROOPS_IN_TILE 1000

#define TROOPS_FOR_CITY 800

#define MIN_TROOP_MOVE 10

/* Misc Deff */
#define NONE 0
#define PLAYER 1
#define COMPUTER 2

/* Terrain Deff */
#define WATER 0
#define LAND  1

/* Piece Deff */
#define AIR 0
#define CITY 1

/* Display Deff */
#define MAP_START_Y 1
#define MAP_START_X 1

#define MAP_HEIGHT 20
#define MAP_WIDTH  80

#define VEIW_HEIGHT 20
#define VEIW_WIDTH  80

#define MESSAGE_START_Y (MAP_HEIGHT + 1)
#define MESSAGE_START_X 0


// Macro to do x to every tile
#define forEveryTile(height, width, x) for(int i = 0; i < height; i++){for(int j = 0; j < width; j++){x}}

struct Location {
    int y;
    int x;
};

struct Terrain {
    int id;
    char tile;
    int color;
};

struct Piece {
    int id;
    char tile;
    int owner;
    int playerTroops = 0;
    int newPlayerTroops = 0;
    int computerTroops = 0;
    int newComputerTroops = 0;
};

struct Tile {
    int terrain;
    Piece piece;
    bool playerFlag = false;
    bool computerFlag = false;
};

// Tile definitions
extern Piece pieceTypes[];
extern Terrain terrainTypes[];

// Map definitions
extern Tile map[MAP_HEIGHT + 2][MAP_WIDTH + 2];
void genMap(double percentWater, int smoothness);

// Display definitions
void printMap();
void printView(int y, int x, int sizeY, int sizeX);
void printCurser(int y, int x);
void pline(const char string[]);

// Misc definitions
void initrand();
int irand(int high);
int igetch();

// Action definitions
void doCommand();

#endif