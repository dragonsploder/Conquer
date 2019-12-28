#include <ncurses.h>


#ifndef KING_H
#define KING_H

#define WATER 0
#define LAND  1

#define MAP_HEIGHT 100//20
#define MAP_WIDTH  400//80
#define VEIW_HEIGHT 20
#define VEIW_WIDTH  80

// Macro to do x to every tile
#define forEveryTile(height, width, x) for(int i = 0; i < height; i++){for(int j = 0; j < width; j++){x}}

typedef struct Piece {
    int id;
    char name[8];
    bool isTerrain;
    char tile;
    int color;
}Piece;

// Map definitons
extern Piece map[MAP_HEIGHT + 2][MAP_WIDTH + 2];
void genMap(double percentWater, int smoothness);

// Display definitons
void printMap();
void printVeiw(int y, int x, int sizeY, int sizeX);

#endif