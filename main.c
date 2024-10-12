/*-------------------------------------------
Program: Totalistic Cellular Automaton
Course: CS 211, Fall 2024, UIC
Author: Guillermo Ramirez III
Date: 9/12/2024
UIN:664042145

This C program simulates a totalistic cellular automaton, where each cell's
state evolves based on its own status and the status of its neighboring cells.
The user inputs a rule number, which determines how the sum of neighboring cell 
states maps to the new state of a cell, and the automaton evolves over a set number 
of generations. The program also displays the progression of the automaton.
------------------------------------------- */



#include <stdio.h>
#include <stdbool.h>

const int WORLD_SIZE = 65;


typedef struct cell_struct{
    int localSum; // total sum of local cells, [left] + [me] + [right]: possible values are 0-6
    int status;   // this cell's current status: 0, 1, or 2
    int count;    // running accumulated count of this cell's active status for all generations
} cell;


bool setValArray(int valArray[7], int rule) {
    //Function converts the input integer rule to its ternary representation

    if((rule >= 0) && (rule <= 2186)){
        for(int i = 0; i < 7; i++){
            valArray[i] = rule % 3;
            rule = rule /3;     
        }
        return true;
    }
        return false;
}

void setSums(cell world[WORLD_SIZE]) {

    //For loop is used in order to update the localSum subitem for each cell in the world,
    // using the current status values for the nearby [left, me, right] cells
    for(int i = 0 ; i < WORLD_SIZE ; i++){
        if(i == 0){
            world[i].localSum = world[64].status + world[i].status + world[i+1].status;
        }
        else if(i == 64){
            world[i].localSum = world[i-1].status + world[i].status + world[0].status;
        }
        else{
            world[i].localSum = world[i-1].status + world[i].status + world[i+1].status;
        }
    }
    return;
}


int evolveWorld(cell world[WORLD_SIZE], int ruleValArray[7]) {

    int totalWorldStatus = 0;

    //For loop is used to evolve each cell's status value to the next generation
    //using its localSum subitem
    for(int i = 0; i  < WORLD_SIZE ; i++){
        int currStatus = ruleValArray[world[i].localSum];
        world[i].status = currStatus;
        world[i].count += currStatus;
        totalWorldStatus += currStatus;
    }

    return totalWorldStatus;
}


int main() {
    cell world[WORLD_SIZE];
    int rule;
    int valArray[7];

    //Welcome :)
    printf("Welcome to the Totalistic Cellular Automaton!\n");

    printf("Enter the rule # (0-2186): ");
    scanf("%d", &rule);

    while(!(setValArray(valArray, rule))){
        printf("\nEnter the rule # (0-2186): ");
        scanf("%d", &rule);
    }

    printf("\n\nThe value array for rule #%d is ", rule);
    
    for(int i = 6; i >= 0; i--){
        printf("%d", valArray[i]);
    }

    printf("\n\nThe evolution of all possible states are as follows:\n");
    printf("Local Sum:   ");

    for(int i = 6; i >= 1; i--){
        printf("%d       ", i);
    }

    printf("0      ");
    printf("\nStates:    |+++|   |++-|   |++ |   |+- |   |-- |   |-  |   |   |    \n                   |+-+|   |+ +|   |+ -|   |- -|   | - |            \n                   |-++|   | ++|   |-+ |   | --|   |  -|            \n                           |+--|   | +-|   |+  |                    \n                           |-+-|   |- +|   | + |                    \n                           |--+|   | -+|   |  +|                    \n                                   |---|                            ");
    printf("\nNew Status: ");

    //For loop is used to print out the new statuses based on the ith place in valArray
    for(int i = 6; i >= 0; i--){
        if(valArray[i] == 2){
            printf("|+|     ");
        }
        else if(valArray[i] == 1){
            printf("|-|     ");
        }
        else if(valArray[i] == 0){
            printf("| |     ");
        }
    }

    printf("\n\nEnter the number of generations (1-49): ");    

    int generations; 
    scanf("%d", &generations);

    while(!((generations >= 1) && (generations <= 49))){
        printf("\nEnter the number of generations (1-49): "); 
        scanf("%d", &generations);
    }
    
    printf("\nEnter the value (1 or 2) for the initial active cell: \n");

    int value;
    scanf("%d", &value);

    while(!((value == 1) || (value == 2))){
        printf("Enter the value (1 or 2) for the initial active cell: \n"); 
        scanf("%d", &value);
    }
    
    printf("\nInitializing world & evolving...\n");
         
    //These 2 if statements starts off our tree (or whatever shape you get) based on the value the user enters
    if(value == 1){
        printf("                                -                                 1 \n");
    }
    else if (value == 2){
        printf("                                +                                 2 \n");
    }

    //Initilizes all of the index's of the world array
    for(int i = 0;i < WORLD_SIZE; i++){
        world[i].status = 0;
        world[i].count = 0;
        world[i].localSum = 0;
    }

    world[WORLD_SIZE/2].status = value;
    int totalWorldStatus = 0;

    for(int i = 0; i < generations - 1; i++){
        setSums(world);
        totalWorldStatus = evolveWorld(world, valArray); //Grabs the sum of all of the array world status numbers

        //This is where the magic happens, the shape that will be printed out will be based
        //on every status number from the world array and will be eihter +,-, or " "
        for(int k = 0; k < WORLD_SIZE; k++){
            if(world[k].status == 1){
                printf("-");
            }
            else if(world[k].status == 2){
                printf("+");
            }
            else if(world[k].status == 0){
                printf(" ");
            }
        }
        printf(" %d \n", totalWorldStatus);
    }
    
    printf("_________________________________________________________________\n");

    //This part prints out the cout numbers that is apart of world and as long as its double digits and divides by 10
    for (int i = 0; i < WORLD_SIZE; i++){
        if(world[i].count >= 10){
            printf("%d", world[i].count / 10);
        }
        else{
            printf(" ");
        }
    }

    printf("\n");

    //Initilizes the singlular middle value to be incremented by the last value input the user has assigned
    world[WORLD_SIZE/2].count += value;

    //This part prints out the cout numbers that is apart of world and as long as its single digits and gets the remainder by 10
    for (int i = 0; i < WORLD_SIZE; i++){
        if(world[i].count == 0){
            printf(" ");
        }
        else{
            printf("%d", world[i].count % 10);
        }   
    }
    printf("\n");

    return 0;
}