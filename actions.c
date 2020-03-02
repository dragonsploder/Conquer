#include "conquer.h"

Location curserLocation = {1, 1};

void moveCurser(int command, bool printInfo){
    printCurser(curserLocation.y, curserLocation.x);
    if (printInfo){
        mvprintw(21,0,"Player: %i      ",map[curserLocation.y][curserLocation.x].piece.playerTroops);
        mvprintw(22,0,"Computer: %i     ",map[curserLocation.y][curserLocation.x].piece.computerTroops);
        mvprintw(23,0,"turnSinceBoat: %i     ",map[curserLocation.y][curserLocation.x].turnSinceBoat);
        //mvprintw(23,0,"numberOfLandTiles: %i     ",map[curserLocation.y][curserLocation.x].piece.numberOfLandTiles);
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

int countTileTypes(int y, int x, int terrain){
    int count = 0;
    if (map[y-1][x].terrain == terrain) count++;
    if (map[y][x].terrain == terrain) count++;
    if (map[y+1][x].terrain == terrain) count++;
    if (map[y-1][x].terrain == terrain) count++;
    if (map[y+1][x].terrain == terrain) count++;
    if (map[y-1][x].terrain == terrain) count++;
    if (map[y][x].terrain == terrain) count++;
    if (map[y+1][x].terrain == terrain) count++;
    return count;
}

void placeCity(int y, int x, int owner){
    map[y][x].piece = pieceTypes[CITY];
    map[y][x].piece.owner = owner; 

    map[y][x].piece.numberOfLandTiles = countTileTypes(y, x, LAND);
    map[y][x].piece.numberOfWaterTiles = countTileTypes(y, x, WATER);

    cities[numberCities] = map[y][x].piece;
    map[y][x].piece.cityLocation = numberCities;
    numberCities++;

    bubblePath((Location) {y, x});
}

void info(int command){
    moveCurser(command, true);
}

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