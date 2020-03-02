#include "conquer.h"
#include <stdlib.h> // Srand, rand 
#include <time.h> // Time 

void initrand(){
    srand(time(0));
}

int irand(int high){
    if (high == 0){
        return 0;
    }
	return (rand() % high);
}

int igetch(){
    return getch();
}
/*struct Path{
    int previousX;
    int previousY;
    int steps;
    int owner;
}*/

void addPath(int y, int x, int i, Path openPaths[], Path tempPaths[], int *tempPathAmount, int currentSteps, int owner, int city){
    if (map[y][x].terrain == LAND && map[y][x].open){
            //printf("Y:%iX%i\n", y, x);
        map[y][x].paths[map[y][x].pathAmount] = {y, x, openPaths[i].y, openPaths[i].x, currentSteps + 1, owner, city};
        map[y][x].open = false;
        tempPaths[*tempPathAmount] = map[y][x].paths[map[y][x].pathAmount];
        map[y][x].pathAmount++;
        (*tempPathAmount)++;
    }
}

void bubblePath(Location originCity){
    struct Path openPaths[100];
    int openPathAmount = 1;
    struct Path tempPaths[100];
    int tempPathAmount = 0;
    int currentSteps = 0;
    int owner = map[originCity.y][originCity.x].piece.owner;
    int city = map[originCity.y][originCity.x].piece.cityLocation;

    openPaths[0] = {originCity.y, originCity.x, 0, 0, currentSteps, owner};

    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        map[i][j].open = true;
    )

    while (openPathAmount != 0){
        for (int i = 0; i < openPathAmount; i++){
            int y = openPaths[i].y;
            int x = openPaths[i].x;
            currentSteps = openPaths[i].steps;
            addPath(y-1, x-1, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner, city);
            addPath(y-1, x, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner, city);
            addPath(y-1, x+1, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner, city);
            addPath(y, x-1, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner, city);
            addPath(y, x+1, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner, city);
            addPath(y+1, x-1, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner, city);
            addPath(y+1, x, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner, city);
            addPath(y+1, x+1, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner, city);
        }
        //printf("OPA:%i\n", openPathAmount);
        for (int i = 0; i < tempPathAmount; i++){
            openPaths[i] = tempPaths[i];
        }
        openPathAmount = tempPathAmount;
        tempPathAmount = 0;
    }
    
}

void updateBubblePath(Piece *originCity){
    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        for (int c = 0; c < map[i][j].pathAmount; c++){
            if (map[i][j].paths[c].city == originCity->cityLocation) {
                map[i][j].paths[c].owner = originCity->owner;
            }
        }
    )
}

struct fancyWord {
    char word[20];
    int underlineLocation;
    bool bold = false;
};

struct fancyWord currentTroopMovement[10] = {
    {"Unused ",0},
    {"Explore",0},
    {"Fortify",0},
    {"Develop",2},
    {"Attack ",1},
    {"Defend ",4}
};

void printCurrentMoment(){
    mvprintw(21,20, "%s", currentTroopMovement[gameFlags.playerTroopMovment].word);
}