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

void addPath(int y, int x, int i, Path openPaths[], Path tempPaths[], int *tempPathAmount, int currentSteps, int owner){
    if (map[y][x].terrain == LAND && map[y][x].open){
            //printf("Y:%iX%i\n", y, x);
        map[y][x].paths[map[y][x].pathAmount] = {y, x, openPaths[i].y, openPaths[i].x, currentSteps + 1, owner};
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

    openPaths[0] = {originCity.y, originCity.x, 0, 0, currentSteps, owner};

    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        map[i][j].open = true;
    )

    while (openPathAmount != 0){
        for (int i = 0; i < openPathAmount; i++){
            int y = openPaths[i].y;
            int x = openPaths[i].x;
            currentSteps = openPaths[i].steps;
            //forEachNeighbor(y, x, 
                addPath(y-1, x-1, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner);
                addPath(y-1, x, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner);
                addPath(y-1, x+1, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner);
                addPath(y, x-1, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner);
                addPath(y, x+1, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner);
                addPath(y+1, x-1, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner);
                addPath(y+1, x, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner);
                addPath(y+1, x+1, i, openPaths, tempPaths, &tempPathAmount, currentSteps, owner);
            //)
            //map[openPaths[i].y][openPaths[i].x].open = false;
        }
        //printf("OPA:%i\n", openPathAmount);
        for (int i = 0; i < tempPathAmount; i++){
            openPaths[i] = tempPaths[i];
        }
        openPathAmount = tempPathAmount;
        tempPathAmount = 0;
    }
    
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