#include "conquer.h"
#include <stdlib.h> // Srand, rand 
#include <time.h> // Time 

void initrand(){
    srand(time(0));
}

int irand(int high){
	return (rand() % high);
}

int igetch(){
    return getch();
}