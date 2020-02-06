#include "conquer.h"

Location curserLocation = {1, 1};

void moveCurser(int command, bool printInfo){
    printCurser(curserLocation.y, curserLocation.x);
    if (printInfo){
        mvprintw(21,0,"Player: %i      ",map[curserLocation.y][curserLocation.x].piece.playerTroops);
        mvprintw(22,0,"Computer: %i     ",map[curserLocation.y][curserLocation.x].piece.computerTroops);
        //mvprintw(21,0,"Y:%i  X:%i ", curserLocation.y, curserLocation.x);
        //mvprintw(22,0,"PY:%i  PX:%i ", map[curserLocation.y][curserLocation.x].paths[1].previousY, map[curserLocation.y][curserLocation.x].paths[1].previousX);
        //mvprintw(23,0,"Steps:%i", map[curserLocation.y][curserLocation.x].paths[1].steps);
    }
    if (command == KEY_RIGHT && curserLocation.x != MAP_WIDTH - 2){
        curserLocation.x++;
    } else if (command == KEY_LEFT && curserLocation.x != 1){
        curserLocation.x--;
    } else if (command == KEY_UP && curserLocation.y != 1){
        curserLocation.y--;
    } else if (command == KEY_DOWN && curserLocation.y != MAP_HEIGHT - 2){
        curserLocation.y++;
    }
}
/*
void makeCity(Location cityLocation){
    map[cityLocation.y][cityLocation.x].piece.id = CITY;
    map[cityLocation.y][cityLocation.x].piece.color = PLAYER_COLOR;
    map[cityLocation.y][cityLocation.x].piece.owner = PLAYER;
    map[cityLocation.y][cityLocation.x].piece.tile = 'O';
}*/

void placeCity(int y, int x, int owner){
    map[y][x].piece = pieceTypes[CITY];
    map[y][x].piece.owner = owner;   
    bubblePath((Location) {y, x});
}

void info(int command){
    moveCurser(command, true);
}
/*
void placeCity(){
    Location tempCityLocation = {MAP_START_Y, MAP_START_X};
    bool goodLocation = false;
    do {
        tempCityLocation = getLocation(tempCityLocation.y, tempCityLocation.x, false);
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
    //makeCity(tempCityLocation);
    map[tempCityLocation.y][tempCityLocation.x].piece = pieceTypes[CITY];
    pline("You made a city.");
}
*/
void doCommand(int command){
    info(command);
    if (command == KEY_ENTER && map[curserLocation.y][curserLocation.x].piece.playerTroops >= gameFlags.playerTroopsForCity && map[curserLocation.y][curserLocation.x].piece.id == AIR){
        int oldTroops = map[curserLocation.y][curserLocation.x].piece.playerTroops;
        placeCity(curserLocation.y, curserLocation.x, PLAYER);
        map[curserLocation.y][curserLocation.x].piece.playerTroops = oldTroops - gameFlags.playerTroopsForCity;
        gameFlags.playerTroopsForCity *= TROOPS_FOR_CITY_MULTIPLIER;
    } else if (command == EXPLORE_KEY){
        gameFlags.playerTroopMovment = EXPLORE;
    } else if (command == FORTIFY_KEY){
        gameFlags.playerTroopMovment = FORTIFY;
    } else if (command == DEVELOP_KEY){
        gameFlags.playerTroopMovment = DEVELOP;
    } else if (command == ATTACK_KEY){
        gameFlags.playerTroopMovment = ATTACK;
    } else if (command == DEFEND_KEY){
        gameFlags.playerTroopMovment = DEFEND;
    } 
};