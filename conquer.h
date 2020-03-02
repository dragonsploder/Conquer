#include <ncurses.h>


#ifndef KING_H
#define KING_H

#define KEY_ENTER 10

#define SECONDS_BETWEEN_TURNS 500

#define PLAYER_COLOR COLOR_CYAN
#define COMPUTER_COLOR COLOR_RED

#define TROOPS_PER_TILE_PER_TURN 10

#define MAX_TROOPS_IN_TILE 500

#define TROOPS_FOR_CITY_MULTIPLIER 1.4

#define MIN_TROOP_MOVE 0.1

#define MAX_TROOP_MOVE 0.5

#define MAX_CITIES 100

/* Troop Movment */
#define EXPLORE 1
#define EXPLORE_KEY 101 // e
#define FORTIFY 2
#define FORTIFY_KEY 102 // f
#define DEVELOP 3
#define DEVELOP_KEY 118 // v
#define ATTACK 4
#define ATTACK_KEY 116 // t
#define DEFEND 5
#define DEFEND_KEY 110 // n

/* Boat stuff */
#define BOAT_PROB_PER_TILE 0.1//0.01
#define MAX_BOAT_CAPACITY 200
#define MIN_BOAT_CAPACITY_TO_MOVE 100
#define BOAT_TOLERANCE 0.1
#define TROOP_LEAVE_BOAT 0.3
#define MIN_BOAT_MOVES_FOR_TROOP_LEAVE 20

/* Owner Deff */
#define NONE 0
#define PLAYER 1
#define COMPUTER 2

/* Terrain Deff */
#define WATER 0
#define LAND  1

/* Piece Deff */
#define AIR 0
#define CITY 1
#define BOAT 2

/* Display Deff */
#define MAP_START_Y 1
#define MAP_START_X 1

#define MAP_HEIGHT 20
#define MAP_WIDTH  80

#define VEIW_HEIGHT 20
#define VEIW_WIDTH  80

#define MESSAGE_START_Y (MAP_HEIGHT + 1)
#define MESSAGE_START_X 0


// Macro to do x to every tile
#define forEveryTile(height, width, x) for(int i = 0; i < height; i++){for(int j = 0; j < width; j++){x}}
/*
#define forEachNeighbor(y, x, function) y--;x--;function;\
                                            x++;function;\
                                            x++;function;\
                                            y++;function;\
                                            y++;function;\
                                            x--;function;\
                                            x--;function;\
                                            y++;function;*/

struct Location {
    int y;
    int x;
};

struct Terrain {
    int id;
    char tile;
    int color;
};

struct Piece {
    int id;
    char tile;
    int owner;
    int playerTroops = 0;
    int newPlayerTroops = 0;
    int computerTroops = 0;
    int newComputerTroops = 0;
    /* City stuff */
    int numberOfLandTiles;
    int numberOfWaterTiles;
    int cityLocation;
    /* Boat stuff */
    bool moveFlag;
    bool boatTroopOnOffFlag = true;
    int lastDropOff;
};

struct Path{
    int y;
    int x;
    int previousY;
    int previousX;
    int steps;
    int owner;
    int city;
};

struct Tile {
    int terrain;
    Piece piece;
    char overrideChar = '0';
    int overrideColor = COLOR_WHITE;
    int overrideMod = A_BOLD;
    /* Troop Movement */
    struct Path paths[20];
    int pathAmount = 0;
    bool open;
    /* Boat movment */
    int turnSinceBoat = -1;
};

struct GameFlags {
    int turn;
    int playerTroopsForCity = 100;
    int computerTroopsForCity = 100;
    int playerTroopMovment = EXPLORE;
};

extern GameFlags gameFlags;

extern Piece cities[];
extern int numberCities;

// Tile definitions
extern Piece pieceTypes[];
extern Terrain terrainTypes[];

// Map definitions
extern Tile map[MAP_HEIGHT + 2][MAP_WIDTH + 2];
void genMap(double percentWater, int smoothness);

// Display definitions
void printMap();
void printView(int y, int x, int sizeY, int sizeX);
void printCurser(int y, int x);
void pline(const char string[]);

// Misc definitions
void initrand();
int irand(int high);
int igetch();
void bubblePath(Location originCity);
void updateBubblePath(Piece *originCity);
void printCurrentMoment();

// Action definitions
void doCommand(int command);
void placeCity(int y, int x, int owner);

// troops deff
void troopActions();

// boat deff
void boatActions();

#endif