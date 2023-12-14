#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define MAX 50

typedef struct SCell{
    int state;
}Cell;

Cell world[MAX][MAX];
Cell buffer[MAX][MAX];

int countNeighbors(int x, int y){
    int sum = 0;
    int rows, cols;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            cols = (x + i + MAX) % MAX; //Relative Position + Wraparound
            rows = (y + j + MAX) % MAX;
            sum += world[cols][rows].state;
        }
    }
    return world[x][y].state == 1? --sum : sum;
}

void UpdateWorld(){
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){

            int nSum = countNeighbors(i, j); //Check Neighborhood

            //printf("%d", nSum); //For Debugging
            //system("pause");

            //Compute New States
            if(nSum == 3 && world[i][j].state == 0) buffer[i][j].state = 1;
            else if((nSum == 2 || nSum == 3) && world[i][j].state == 1) buffer[i][j].state = world[i][j].state;
            else buffer[i][j].state = 0;
        }
    }
    //Update World with New Values
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            world[i][j].state = buffer[i][j].state;
}

void FillWorld(){
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            world[i][j].state = rand()%2;
        }
    }
}

void PrintWorld(){
    const HANDLE std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    const COORD top_left = {0, 0};
    SetConsoleCursorPosition(std_handle, top_left);

    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++)
            world[i][j].state == 1? fputs("@ ", stdout) : fputs("  ", stdout);
        putc('\n', stdout);
    }
}

int main(){
    srand(time(NULL));
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

    FillWorld(); //Initial Fill
    PrintWorld();
    //system("pause"); //For Debugging
    while(1){
        UpdateWorld();
        PrintWorld();
        //system("pause"); //For Debugging
    }
}
