#include "conquer.h"

void makeBoat(Piece *location, int owner){
    *location = pieceTypes[BOAT];
    location->owner = owner;
}

void moveBoat(Piece *newPiece, Piece *oldPiece){
    *newPiece = *oldPiece;
    newPiece->moveFlag = true;
    *oldPiece = pieceTypes[AIR];
    oldPiece->owner = NONE;
}

void addBoat(Tile *currentTile, int y, int x){
    if (irand(100) <= currentTile->piece.numberOfWaterTiles * BOAT_PROB_PER_TILE * 100){
        Location boatLocation;
        //do {
            boatLocation = {y, x};
            boatLocation.y += irand(3) - 1;
            boatLocation.x += irand(3) - 1;
        //} while (map[boatLocation.y][boatLocation.x].terrain == LAND);
        if (map[boatLocation.y][boatLocation.x].terrain == WATER && map[boatLocation.y][boatLocation.x].piece.id != BOAT
         && (boatLocation.y != 0 && boatLocation.y != MAP_HEIGHT) && (boatLocation.x != 0 && boatLocation.x != MAP_WIDTH)){ // Dont place off map){
            makeBoat(&map[boatLocation.y][boatLocation.x].piece, map[y][x].piece.owner);
            map[boatLocation.y][boatLocation.x].turnSinceBoat = 0;
            /*
            map[boatLocation.y][boatLocation.x].piece = pieceTypes[BOAT];
            map[boatLocation.y][boatLocation.x].piece.owner = map[y][x].piece.owner;
            map[boatLocation.y][boatLocation.x].piece.moveFlag = true; // New boats shouldn't move first turn
            */
        }
    }
}

void updateBoats(Piece *currentPiece){
    // fail safe
    currentPiece->playerTroops += currentPiece->newPlayerTroops;
    currentPiece->newPlayerTroops = 0;
    if (currentPiece->playerTroops > MAX_BOAT_CAPACITY){
        currentPiece->playerTroops = MAX_BOAT_CAPACITY;
    }
    currentPiece->moveFlag = false;

    if (currentPiece->playerTroops >= MIN_BOAT_CAPACITY_TO_MOVE && currentPiece->boatTroopOnOffFlag){
        currentPiece->boatTroopOnOffFlag = false;
    }
    if (!currentPiece->boatTroopOnOffFlag && (gameFlags.turn - currentPiece->lastDropOff > MIN_BOAT_MOVES_FOR_TROOP_LEAVE) && irand(4) > 2){
        currentPiece->boatTroopOnOffFlag = true;
    }
}

void moveBoats(Tile *currentTile, int y, int x){
    if (!currentTile->piece.boatTroopOnOffFlag && gameFlags.playerTroopMovment != FORTIFY && !currentTile->piece.moveFlag){
        Location tileToMoveTo = {y, x};
        if (gameFlags.playerTroopMovment == EXPLORE){
            //tileToMoveTo.y = y + (irand(3) - 1);
            //tileToMoveTo.x = x + (irand(3) - 1);
            int longestTimeSinceBoat = 0;
            Location longestTimeSinceBoatLocation = {y, x};
            if (map[tileToMoveTo.y + 1][tileToMoveTo.x + 1].turnSinceBoat > longestTimeSinceBoat /*&& irand(100) > BOAT_TOLERANCE * 100*/){longestTimeSinceBoat = map[longestTimeSinceBoatLocation.y][longestTimeSinceBoatLocation.x].turnSinceBoat;longestTimeSinceBoatLocation.y=y+1;longestTimeSinceBoatLocation.x=x+1;}
            if (map[tileToMoveTo.y + 1][tileToMoveTo.x].turnSinceBoat > longestTimeSinceBoat){longestTimeSinceBoat = map[longestTimeSinceBoatLocation.y][longestTimeSinceBoatLocation.x].turnSinceBoat;longestTimeSinceBoatLocation.y=y+1;}
            if (map[tileToMoveTo.y + 1][tileToMoveTo.x - 1].turnSinceBoat > longestTimeSinceBoat){longestTimeSinceBoat = map[longestTimeSinceBoatLocation.y][longestTimeSinceBoatLocation.x].turnSinceBoat;longestTimeSinceBoatLocation.y=y+1;longestTimeSinceBoatLocation.x=x-1;}
            if (map[tileToMoveTo.y][tileToMoveTo.x - 1].turnSinceBoat > longestTimeSinceBoat){longestTimeSinceBoat = map[longestTimeSinceBoatLocation.y][longestTimeSinceBoatLocation.x].turnSinceBoat;longestTimeSinceBoatLocation.x=x+1;}
            if (map[tileToMoveTo.y][tileToMoveTo.x + 1].turnSinceBoat > longestTimeSinceBoat){longestTimeSinceBoat = map[longestTimeSinceBoatLocation.y][longestTimeSinceBoatLocation.x].turnSinceBoat;longestTimeSinceBoatLocation.x=x-1;}
            if (map[tileToMoveTo.y - 1][tileToMoveTo.x + 1].turnSinceBoat > longestTimeSinceBoat){longestTimeSinceBoat = map[longestTimeSinceBoatLocation.y][longestTimeSinceBoatLocation.x].turnSinceBoat;longestTimeSinceBoatLocation.y=y-1;longestTimeSinceBoatLocation.x=x+1;}
            if (map[tileToMoveTo.y - 1][tileToMoveTo.x].turnSinceBoat > longestTimeSinceBoat){longestTimeSinceBoat = map[longestTimeSinceBoatLocation.y][longestTimeSinceBoatLocation.x].turnSinceBoat;longestTimeSinceBoatLocation.y=y-1;}
            if (map[tileToMoveTo.y - 1][tileToMoveTo.x - 1].turnSinceBoat > longestTimeSinceBoat){longestTimeSinceBoat = map[longestTimeSinceBoatLocation.y][longestTimeSinceBoatLocation.x].turnSinceBoat;longestTimeSinceBoatLocation.y=y-1;longestTimeSinceBoatLocation.x=x-1;}
            tileToMoveTo = longestTimeSinceBoatLocation;
        }

        if (map[tileToMoveTo.y][tileToMoveTo.x].terrain == WATER && map[tileToMoveTo.y][tileToMoveTo.x].piece.id == AIR
                 && (tileToMoveTo.y != 0 && tileToMoveTo.y != MAP_HEIGHT) && (tileToMoveTo.x != 0 && tileToMoveTo.x != MAP_WIDTH)){ // Dont move off map
            moveBoat(&map[tileToMoveTo.y][tileToMoveTo.x].piece, &currentTile->piece);
            map[tileToMoveTo.y][tileToMoveTo.x].turnSinceBoat = 0;
            /*
            map[tileToMoveTo.y][tileToMoveTo.x].piece = map[y][x].piece;
            currentTile->piece = pieceTypes[BOAT];
            currentTile->piece = pieceTypes[BOAT];
            */
        }
    }
}

void boatActions(){
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        Tile *currentTile = &map[i][j];
        if (currentTile->piece.id == CITY){
            addBoat(currentTile, i, j);
        }
    )

    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        Tile *currentTile = &map[i][j];
        if (currentTile->piece.id == BOAT){
            moveBoats(currentTile, i, j);
        }
    )

    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        Piece *currentPiece = &map[i][j].piece;
        if (currentPiece->id == BOAT){
            updateBoats(currentPiece);
        }
    )
    forEveryTile(MAP_HEIGHT - 2, MAP_WIDTH - 2,
        map[i+1][j+1].turnSinceBoat++;
    )

}