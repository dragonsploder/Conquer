#include "conquer.h"

void printMap(){
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        if (map[i][j].piece.id == AIR){
            if (map[i][j].piece.playerTroops > map[i][j].piece.computerTroops){
                attron(COLOR_PAIR(PLAYER_COLOR)|A_BOLD);
            } else if (map[i][j].piece.computerTroops > map[i][j].piece.playerTroops){
                attron(COLOR_PAIR(COMPUTER_COLOR));
            } else {
                attron(COLOR_PAIR(terrainTypes[map[i][j].terrain].color));
            }
            mvprintw(i, j, "%c", terrainTypes[map[i][j].terrain].tile);
        } else {
            attron(COLOR_PAIR(map[i][j].piece.color));
            mvprintw(i, j, "%c", map[i][j].piece.tile);
        }
        attrset(A_NORMAL);
    )
}

void printView(int y, int x, int sizeY, int sizeX){
    forEveryTile(sizeY, sizeX,
        if (map[i][j].piece.id == AIR){
            attron(COLOR_PAIR(terrainTypes[map[i+y][j+x].terrain].color));
            mvprintw(i, j, "%c", terrainTypes[map[i+y][j+x].terrain].tile);
        } else {
            attron(COLOR_PAIR(map[i+y][j+x].piece.color));
            mvprintw(i, j, "%c", map[i+y][j+x].piece.tile);
        }
    )
}

void printCurser(int y, int x){
    attron(COLOR_PAIR(COLOR_WHITE)|A_BOLD);
    mvprintw(y-1, x, "|");
    mvprintw(y, x-1, "-");
    mvprintw(y, x+1, "-");
    mvprintw(y+1, x, "|");
    attrset(A_NORMAL);
}

void pline(const char string[]){
    mvprintw(MESSAGE_START_Y, MESSAGE_START_X, string);
}