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

/*
struct Node {
    int y;
    int x;
    int fCost;
    int gCost;
    bool open;
    int parentY;
    int parentX;
};

void updateFCost(int i, int j, Node nodes[MAP_HEIGHT][MAP_WIDTH], Location start, Location goal, Node current){
    if (map[i+1][j+1].terrain == LAND && nodes[i][j].open){
        int newGCost = current.gCost + 1;
        int newFCost = newGCost + (abs(nodes[i][j].y - goal.y) + abs(nodes[i][j].x - goal.x));
        printf("Y:%i,X:%i fcost%i\n", i, j, newFCost);
        if (newGCost < nodes[i][j].gCost){
            nodes[i][j].gCost = newGCost;
            nodes[i][j].fCost = newFCost;
            nodes[i][j].parentY = current.y;
            nodes[i][j].parentX = current.x;
            nodes[i][j].open = true;
        }
    }
}


Location AStar(Location start, Location goal, bool overLand){

    Node nodes[MAP_HEIGHT][MAP_WIDTH];

    forEveryTile(MAP_HEIGHT, MAP_WIDTH,
        nodes[i][j].y = i;
        nodes[i][j].x = j;
        nodes[i][j].fCost = 1000;
        nodes[i][j].gCost = 1000;
        nodes[i][j].open = true;
    );

    //nodes[start.y][start.x] = {start.y, start.x, (abs(start.y - goal.y) + abs(start.x - goal.x)), false};
    nodes[start.y][start.x] = {start.y, start.x, 0, 0, false};

    //Node *current = &nodes[start.y][start.x];
    Node current = nodes[start.y][start.x];


    while (true){
        //printf("y:%i\nx:%i", current.y, current.x);

        //printf("Next\n");


        if (current.y == goal.y && current.x == goal.x){
            while(true){
                printf("Stuck\n");
                current = nodes[current.parentY][current.parentX];
                if (current.parentY == start.y && current.parentX == start.x){
                    return (Location) {current.y, current.x};
                }
            }
        }

        int i = current.y;
        int j = current.x;
        //printf("currentY:%i X:%i\n", i, j);

        updateFCost(i-1,j-1,nodes,start,goal,current);
        updateFCost(i-1,j,nodes,start,goal,current);
        updateFCost(i-1,j+1,nodes,start,goal,current);
        updateFCost(i,j-1,nodes,start,goal,current);
        updateFCost(i,j+1,nodes,start,goal,current);
        updateFCost(i+1,j-1,nodes,start,goal,current);
        updateFCost(i+1,j,nodes,start,goal,current);
        updateFCost(i+1,j+1,nodes,start,goal,current);



        
        forEachNeighbor(i, j, 
           updateFCost(i,j,nodes,start,goal,current);
        );

        Node tempNode;
        tempNode.fCost = 1000;
        forEveryTile(MAP_HEIGHT, MAP_WIDTH,
            //printf("node[%i][%i]:%i\n", i, j, nodes[i][j].fCost);
            if (nodes[i][j].open && tempNode.fCost > nodes[i][j].fCost){
                tempNode.y = i;
                tempNode.x = j;
                tempNode.fCost = nodes[i][j].fCost;
            }
        );

        current = nodes[tempNode.y][tempNode.x];
        current.open = false;

    }

}*/