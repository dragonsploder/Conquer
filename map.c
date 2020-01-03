#include "conquer.h"

Tile map[MAP_HEIGHT + 2][MAP_WIDTH + 2];
Tile tempMap[MAP_HEIGHT + 2][MAP_WIDTH + 2];

void genMap(double percentLand, int smoothness){

    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
       map[i][j].piece = pieceTypes[AIR];
    )

    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        map[i][j].terrain = WATER;
        tempMap[i][j].terrain = WATER;
    )
    for(int i = 0; i < (int)(MAP_HEIGHT * MAP_WIDTH * percentLand); i++){
        map[irand(MAP_HEIGHT - 2) + 1][irand(MAP_WIDTH - 2) + 1].terrain = LAND;
    }

    for(int s = 0; s < smoothness; s++){
        forEveryTile(MAP_HEIGHT - 2, MAP_WIDTH - 2,
            int neighbors = 0;
            neighbors+=map[i+2][j+2].terrain;
            neighbors+=map[i+2][j+1].terrain;
            neighbors+=map[i+2][j].terrain;
            neighbors+=map[i+1][j+2].terrain;
            neighbors+=map[i+1][j].terrain;
            neighbors+=map[i][j+2].terrain;
            neighbors+=map[i][j+1].terrain;
            neighbors+=map[i][j].terrain;
            if(neighbors < 4){
                tempMap[i+1][j+1].terrain = WATER;
            } else if(neighbors > 3){
                tempMap[i+1][j+1].terrain = LAND;
            }
        )
        forEveryTile(MAP_HEIGHT, MAP_WIDTH,
            map[i][j].terrain = tempMap[i][j].terrain;
        )
    }
}