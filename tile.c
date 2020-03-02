#include "conquer.h"

Piece pieceTypes[] = {
    {AIR, ' ', NONE},
    {CITY, 'O', NONE},
    {BOAT, '=', NONE}
};

Terrain terrainTypes[] = {
    {WATER, '.', COLOR_BLUE},
    {LAND, '#', COLOR_GREEN}
};