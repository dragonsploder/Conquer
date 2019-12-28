#include "conquer.h"

void printMap(){
    forEveryTile(MAP_HEIGHT + 2, MAP_WIDTH + 2,
        attron(COLOR_PAIR(map[i][j].color));
        mvprintw(i, j, "%c", map[i][j].tile);
    )
}

void printVeiw(int y, int x, int sizeY, int sizeX){
    forEveryTile(sizeY, sizeX,
        attron(COLOR_PAIR(map[i+y][j+x].color));
        mvprintw(i, j, "%c", map[i+y][j+x].tile);
    )
}