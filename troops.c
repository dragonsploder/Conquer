#include "conquer.h"
#include <math.h>

void addCityPop(Piece *currentPiece){
    if (currentPiece->owner == PLAYER){
        currentPiece->newPlayerTroops += (TROOPS_PER_TILE_PER_TURN * currentPiece->numberOfLandTiles);
    } else if (currentPiece->owner == COMPUTER){
        currentPiece->newComputerTroops += (TROOPS_PER_TILE_PER_TURN * currentPiece->numberOfLandTiles);
    }
}

void moveTroops(Piece *currentPiece, int y, int x){
    if (map[y][x].terrain == LAND || currentPiece->id == BOAT){
            // player
            if (gameFlags.playerTroopMovment != FORTIFY || !(gameFlags.playerTroopMovment == DEFEND && currentPiece->id == CITY && currentPiece->owner == PLAYER)){ // Dont move if fortify or if in defending player city
                for (int c = 0; c < 8; c++){
                    int minTroopMove = (int) currentPiece->playerTroops * MIN_TROOP_MOVE;
                    int maxTroopMove;
                    if (gameFlags.playerTroopMovment == DEVELOP && currentPiece->playerTroops >= gameFlags.playerTroopsForCity){ // Might want to change the way this works
                        maxTroopMove = currentPiece->playerTroops - gameFlags.playerTroopsForCity;
                        if (maxTroopMove < minTroopMove){
                            maxTroopMove = 0;
                            minTroopMove = 0;
                        }
                        if (maxTroopMove > (int) currentPiece->playerTroops * MAX_TROOP_MOVE){
                            maxTroopMove = (int) currentPiece->playerTroops * MAX_TROOP_MOVE;
                        }
                    } else {
                        maxTroopMove = (int) currentPiece->playerTroops * MAX_TROOP_MOVE;
                    }
                    int troopsToMove = irand(maxTroopMove - minTroopMove) + minTroopMove;


                    Location cityToMoveTo = {y, x};
                    if (gameFlags.playerTroopMovment == ATTACK && map[y][x].pathAmount > 1){
                        int randomCity = 0;
                        //mvprintw(23,0, "randomCity:%i", randomCity);
                        while (map[y][x].paths[randomCity].owner != COMPUTER){
                            randomCity = irand(map[y][x].pathAmount);
                        }
                        cityToMoveTo.y = map[y][x].paths[randomCity].previousY;
                        cityToMoveTo.x = map[y][x].paths[randomCity].previousX;

                    } else if (gameFlags.playerTroopMovment == DEFEND && map[y][x].pathAmount > 0){
                        if (!(map[y][x].piece.id == CITY && map[y][x].piece.owner == PLAYER)){
                            int shortestPath = 0;
                            for (int i = 0; i < map[y][x].pathAmount; i++){
                                if (map[y][x].paths[i].owner == PLAYER){
                                    shortestPath = i;
                                    break;
                                }
                            }
                            for (int i = 0; i < map[y][x].pathAmount; i++){
                                if (map[y][x].paths[i].owner == PLAYER && map[y][x].paths[i].steps < map[y][x].paths[shortestPath].steps){
                                    shortestPath = i;
                                }
                            }
                            cityToMoveTo.y = map[y][x].paths[shortestPath].previousY;
                            cityToMoveTo.x = map[y][x].paths[shortestPath].previousX;
                        } else {
                            cityToMoveTo.y = y;
                            cityToMoveTo.x = x;
                        }

                    } else if (!(currentPiece->id == BOAT /*&& irand(100) > TROOP_LEAVE_BOAT * 100*/ && !currentPiece->boatTroopOnOffFlag)){
                        cityToMoveTo.y = y + (irand(3) - 1);
                        cityToMoveTo.x = x + (irand(3) - 1);
                    }

                    if (map[cityToMoveTo.y][cityToMoveTo.x].piece.playerTroops + troopsToMove <= MAX_TROOPS_IN_TILE && map[cityToMoveTo.y][cityToMoveTo.x].terrain == LAND){
                        map[cityToMoveTo.y][cityToMoveTo.x].piece.newPlayerTroops += troopsToMove;
                        currentPiece->playerTroops -= troopsToMove;
                    } else if (map[cityToMoveTo.y][cityToMoveTo.x].piece.id == BOAT && map[cityToMoveTo.y][cityToMoveTo.x].piece.owner == PLAYER && map[cityToMoveTo.y][cityToMoveTo.x].piece.playerTroops + troopsToMove <= MAX_BOAT_CAPACITY){
                        map[cityToMoveTo.y][cityToMoveTo.x].piece.newPlayerTroops += troopsToMove;
                        currentPiece->playerTroops -= troopsToMove;
                    }

                    //if (map[i + cityOffset.y][j + cityOffset.x].terrain == LAND && map[i + cityOffset.y][j + cityOffset.x].piece.playerTroops + troopsToMove <= MAX_TROOPS_IN_TILE){
                    //    map[i + cityOffset.y][j + cityOffset.x].piece.newPlayerTroops += troopsToMove;
                    //    currentPiece->playerTroops -= troopsToMove;
                    //}
                }
            }
            // computer
            for (int c = 0; c < 9; c++){
                int maxTroopMove = (int) currentPiece->computerTroops * MAX_TROOP_MOVE;
                int minTroopMove = (int) currentPiece->computerTroops * MIN_TROOP_MOVE;
                int troopsToMove = irand(maxTroopMove - minTroopMove) + minTroopMove;
                Location cityOffset;
                cityOffset.y = (irand(3) - 1);
                cityOffset.x = (irand(3) - 1);
                if (map[y + cityOffset.y][x + cityOffset.x].terrain == LAND && map[y + cityOffset.y][x + cityOffset.x].piece.computerTroops + troopsToMove <= MAX_TROOPS_IN_TILE){
                    map[y + cityOffset.y][x + cityOffset.x].piece.newComputerTroops += troopsToMove;
                    currentPiece->computerTroops -= troopsToMove;
                }
            }
        }
}

void fight(Piece *currentPiece){
    
    if (currentPiece->playerTroops > currentPiece->computerTroops){
        currentPiece->playerTroops -= currentPiece->computerTroops;
        currentPiece->computerTroops = 0;
    } else if (currentPiece->computerTroops > currentPiece->playerTroops){
        currentPiece->computerTroops -= currentPiece->playerTroops;
        currentPiece->playerTroops = 0;
    }
    /*
    int diff = abs(currentPiece->playerTroops - currentPiece->computerTroops);
    currentPiece->playerTroops -= irand(diff);
    currentPiece->computerTroops -= irand(diff);
    if (currentPiece->playerTroops < 0){
        currentPiece->playerTroops = 0;
    }
    if (currentPiece->computerTroops < 0){
        currentPiece->computerTroops = 0;
    }*/
}

void updateTroops(Piece *currentPiece){
    currentPiece->playerTroops += currentPiece->newPlayerTroops;
    currentPiece->newPlayerTroops = 0;
    if (currentPiece->playerTroops > MAX_TROOPS_IN_TILE){
        currentPiece->playerTroops = MAX_TROOPS_IN_TILE;
    }

    currentPiece->computerTroops += currentPiece->newComputerTroops;
    currentPiece->newComputerTroops = 0;
    if (currentPiece->computerTroops > MAX_TROOPS_IN_TILE){
        currentPiece->computerTroops = MAX_TROOPS_IN_TILE;
    }

    if (currentPiece->id == CITY){
        if (currentPiece->owner == PLAYER && currentPiece->playerTroops < currentPiece->computerTroops){
            currentPiece->owner = COMPUTER;
            updateBubblePath(currentPiece);
        } else if (currentPiece->owner == COMPUTER && currentPiece->computerTroops < currentPiece->playerTroops){
            currentPiece->owner = PLAYER;
        }
    }
}


void troopActions(){
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        Piece *currentPiece = &map[i][j].piece;
        if (currentPiece->id == CITY){
            addCityPop(currentPiece);
        }
    )
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        Piece *currentPiece = &map[i][j].piece;
        moveTroops(currentPiece, i, j);
    )
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        Piece *currentPiece = &map[i][j].piece;
        fight(currentPiece);
    )
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        Piece *currentPiece = &map[i][j].piece;
        updateTroops(currentPiece);
    )
}