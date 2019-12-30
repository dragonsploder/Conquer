#include "conquer.h"

Location getLocation(int startY, int startX){
    Location curserLocation = {startY, startX};
    int cmd;
    while(cmd != 10){
        printMap();
        printCurser(curserLocation.y, curserLocation.x);
        cmd = igetch();
        if (cmd == KEY_RIGHT && curserLocation.x != MAP_WIDTH - 2){
            curserLocation.x++;
        } else if (cmd == KEY_LEFT && curserLocation.x != 1){
            curserLocation.x--;
        } else if (cmd == KEY_UP && curserLocation.y != 1){
            curserLocation.y--;
        } else if (cmd == KEY_DOWN && curserLocation.y != MAP_HEIGHT - 2){
            curserLocation.y++;
        }
    }
    return curserLocation;
}

void makeCity(Location cityLocation){
    map[cityLocation.y][cityLocation.x].piece.id = CITY;
    map[cityLocation.y][cityLocation.x].piece.color = PLAYER_COLOR;
    map[cityLocation.y][cityLocation.x].piece.owner = PLAYER;
    map[cityLocation.y][cityLocation.x].piece.tile = 'O';
}

void placeCity(){
    Location tempCityLocation = {MAP_START_Y, MAP_START_X};
    bool goodLocation = false;
    do {
        tempCityLocation = getLocation(tempCityLocation.y, tempCityLocation.x);
        if (map[tempCityLocation.y][tempCityLocation.x].piece.id == AIR){
            if (terrainTypes[map[tempCityLocation.y][tempCityLocation.x].terrain].id == LAND){
                goodLocation = true;
            } else {
                pline("You can't build a city here.");
            }
        } else {
            pline("There's already something here.");
        }
    } while (!goodLocation);
    makeCity(tempCityLocation);
    pline("You made a city.");
}

void doCommand(){
    placeCity();
};