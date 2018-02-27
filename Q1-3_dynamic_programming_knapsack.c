/*
Project 3 - dynamic programming algorithm for 0/1 knapsack.​
By Aravind Venkit
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

//Declaration of global variables
int itemsCount = 0;
int capacity = 0;
//Declaration of struct
struct Inventory
{
    int *weight;
    int *profit;
};

//Declaration of struct array called phDirectory
struct Inventory *inventory;

 /*LoadFile function retrives each line of data from given file.
 */
void LoadFile(char fileName[]){
    int indx = 0;
    //Intializing file
    FILE *file = fopen(fileName, "r");
    // Check whether the file is correct one
    if(!file){
        fprintf(stderr, "Can't onpen the file %s", fileName);
    }
    char buf[100] = "";
    // Use buffer char to get inputs line by line in file
    while(fgets(buf, 100, file)){
        if(buf[strlen(buf)-1] == '\n'){
           buf[strlen(buf)-1] = '\0';
       }
       
       if(indx == 0){
        //The # items is loaded to itemsCount
        itemsCount = atoi(buf);
        //Memorey allocation for the inventory struct.
        inventory = malloc( sizeof( struct Inventory ) * itemsCount);
        inventory->weight = malloc( sizeof( int ) * itemsCount);
        inventory->profit = malloc( sizeof( int ) * itemsCount);
       }

       if(indx == 1){
        //The respective items weight are loaded to struct inventory.
        char *str = strtok(buf, ",");
        int i =0;
        for(i = 0; i<itemsCount; i++){
            inventory->weight[i] = atoi(str);
             str = strtok(NULL, ",");
        }
        free(str);
       }
       if(indx == 2){
        //The respective items profit are loaded to struct inventory.
        char *str = strtok(buf, ",");
        int i =0;
        for(i = 0; i<itemsCount; i++){
            inventory->profit[i] = atoi(str);
             str = strtok(NULL, ",");
        }
        free(str);
       }
       if(indx == 3){
        //The knapsack capacity is loaded to capacity.
        capacity = atoi(buf);
       }
        indx++;
    }  
    // File closed 
    fclose(file);
}

int main(int argc, char *argv[])
{
    //Get file name as argument or take knapsack.txt as default file name
    char fileName[30];
    if(argv[1] == NULL){
        strcpy(fileName, "knapsack.txt");
    }
    else{
        strcpy(fileName, argv[1]);
    }
    // load file method is called
    LoadFile(fileName);
    // Variables are delared and intialized
    int k=0,w=0; 
    int profitMatrix[itemsCount+1][capacity+1]; // To calculate and get the final total profit
    int weightMatrix[itemsCount+1][capacity+1]; // To calculate and get the final total weight
    int status[itemsCount+1][capacity+1];
    int selectedItems[itemsCount]; // To cstore final selected knapsac items

    // Intializing the capacity collumns to 0
    for(w=0; w <= capacity; w++){
        profitMatrix[0][w] = 0;
        weightMatrix[0][w] = 0;
    }    
    
    // To calculate the Optimal solution using dynamic programming
    for(k = 1; k <= itemsCount; k++){  
        //intializing the rows to 0
        profitMatrix[k][0] = 0;
        weightMatrix[k][0] = 0;
        //intializes the selectedItems to -1
        selectedItems[k-1] = -1;
        for(w=0; w<=capacity; w++){
            // for each column w the respective weights and profit are calculated to get the optimal solution
            if(inventory->weight[k] <= w && 
                (profitMatrix[k-1][w - inventory->weight[k-1]]+ inventory->profit[k-1]) > profitMatrix[k-1][w])
            {
                // every new combination is will get to here and continues to search for effective solution
                profitMatrix[k][w] = profitMatrix[k-1][w - inventory->weight[k-1]] + inventory->profit[k-1];
                weightMatrix[k][w] = weightMatrix[k-1][w-inventory->weight[k-1]] + inventory->weight[k-1];
                status[k][w] = 1;
            }
            else{
                // if the previous solution repeats no other effective solution is yet to detected the else part will execute.
                profitMatrix[k][w] = profitMatrix[k-1][w];
                weightMatrix[k][w] = weightMatrix[k-1][w];
                status[k][w] = 0;
            } 
        }
    }

    int i= itemsCount-1, item=0, cap = capacity;
    while(i > 0){
        if(status[i][cap] == 1){
            selectedItems[item++] = i;
            cap = cap - inventory->weight[i];
        }
        i--;
    }

    // Required output is printed
    //First the total selected item
    printf("\n------------Total----------------\n");
    printf("weight = %d, profit = %d\n", weightMatrix[itemsCount][capacity], profitMatrix[itemsCount][capacity]);
    //Second details of selected items
    printf("\n---------Selected item's---------\n");
    for(i = 0; i < itemsCount; i++){
        if(selectedItems[i]!=-1){
            printf("item %d, weight = %d, profit = %d\n", i+1, inventory->weight[selectedItems[i]],
             inventory->profit[selectedItems[i]]);
        }
    }    
    // Free's the memorey allocated to inventory struct
    free(inventory->weight);
    free(inventory->profit);
    free(inventory);
    return 0; 
}
