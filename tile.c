#include "conquer.h"

Piece pieceTypes[] = {
    {AIR, ' ', COLOR_BLACK, NONE,0,0,0,0},
    {CITY, 'O', PLAYER_COLOR, PLAYER,0,0,0,0}
};

Terrain terrainTypes[] = {
    {WATER, '.', COLOR_BLUE},
    {LAND, '#', COLOR_GREEN}
};