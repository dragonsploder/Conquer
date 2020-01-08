#include "conquer.h"

void printMap(){
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        int color;
        int mod = A_NORMAL;
        if (map[i][j].overrideChar != '0'){
            attron(COLOR_PAIR(map[i][j].overrideColor)|map[i][j].overrideMod);
            mvprintw(i, j, "%c", map[i][j].overrideChar);
        } else if (map[i][j].piece.id == AIR){
            if (map[i][j].piece.playerTroops == 0 && map[i][j].piece.computerTroops == 0){
                color = terrainTypes[map[i][j].terrain].color;
            } else if (map[i][j].piece.computerTroops >= map[i][j].piece.playerTroops){
                color = COMPUTER_COLOR;
                if (map[i][j].piece.computerTroops >= gameFlags.computerTroopsForCity){
                    mod = A_BOLD;
                }
            } else if (map[i][j].piece.playerTroops > map[i][j].piece.computerTroops) {
                color = PLAYER_COLOR;
                if (map[i][j].piece.playerTroops >= gameFlags.playerTroopsForCity){
                    mod = A_BOLD;
                }
            }
            attron(COLOR_PAIR(color)|mod);
            mvprintw(i, j, "%c", terrainTypes[map[i][j].terrain].tile);
        } else {
            if (map[i][j].piece.owner == PLAYER){
                color = PLAYER_COLOR;
            } else if (map[i][j].piece.owner == COMPUTER){
                color = COMPUTER_COLOR;
            } else {
                color = COLOR_WHITE;
            }
            attron(COLOR_PAIR(color)|mod);
            mvprintw(i, j, "%c", map[i][j].piece.tile);
        }
        attrset(A_NORMAL);
    )
}
/*
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
}*/

void clearOverridChar(){
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        map[i][j].overrideChar = '0';
    )
}

void printCurser(int y, int x){
    clearOverridChar();
    map[y-1][x].overrideChar = '|';
    map[y][x-1].overrideChar = '-';
    map[y][x+1].overrideChar = '-';
    map[y+1][x].overrideChar = '|';
}

void pline(const char string[]){
    mvprintw(MESSAGE_START_Y, MESSAGE_START_X, string);
}

void printScreenOutline(){

}

