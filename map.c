#include "conquer.h"
#include <stdlib.h> // Srand, rand 
#include <time.h> // Time 

Piece map[MAP_HEIGHT + 2][MAP_WIDTH + 2];
Piece tempMap[MAP_HEIGHT + 2][MAP_WIDTH + 2];

Piece land = {LAND, "land", true, '#', COLOR_GREEN};
Piece water = {WATER, "water", true, '.', COLOR_CYAN};

void genMap(double percentLand, int smoothness){
    srand(time(0));
    forEveryTile(MAP_HEIGHT + 2, MAP_WIDTH + 2,
        map[i][j] = water;
        tempMap[i][j] = water;
    )
    for(int i = 0; i < (int)(MAP_HEIGHT * MAP_WIDTH * percentLand); i++){
        map[(rand() % MAP_HEIGHT) + 1][(rand() % MAP_WIDTH) + 1] = land;
    }

    for(int s = 0; s < smoothness; s++){
        forEveryTile(MAP_HEIGHT, MAP_WIDTH,
            int neighbors = 0;
            neighbors+=map[i+2][j+2].id;
            neighbors+=map[i+2][j+1].id;
            neighbors+=map[i+2][j].id;
            neighbors+=map[i+1][j+2].id;
            neighbors+=map[i+1][j].id;
            neighbors+=map[i][j+2].id;
            neighbors+=map[i][j+1].id;
            neighbors+=map[i][j].id;
            if(neighbors < 4){
                tempMap[i+1][j+1] = water;
            } else if(neighbors > 3){
                tempMap[i+1][j+1] = land;
            }
        )
        forEveryTile(MAP_HEIGHT, MAP_WIDTH,
            map[i][j] = tempMap[i][j];
        )
    }
}