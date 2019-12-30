#include <ncurses.h>


#ifndef KING_H
#define KING_H

#define KEY_ENTER 10

#define PLAYER_COLOR COLOR_CYAN

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

typedef struct Location {
    int y;
    int x;
} Location;

typedef struct Terrain {
    int id;
    char tile;
    int color;
} Terrain;

typedef struct Piece {
    int id;
    char tile;
    int color;
    int owner;
} Piece;

typedef struct Tile {
    int terrain;
    Piece piece;
} Tile;

// Tile definitions
extern Piece air;
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