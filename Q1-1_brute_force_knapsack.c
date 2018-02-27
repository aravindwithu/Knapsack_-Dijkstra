/*
Project 2 - Brut force algorithm for 0/1 knapsack.​
By Aravind Venkit
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

//Declaration of struct array called inventory
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
    int i = 0;
    int j = 0;
    int weightSol = 0;//Final total weight solution
    int profitSol = 0; //Final total profit solution
    int sets = pow(2, itemsCount);//To get all the permutation sets of the given items
    int selectedItems[itemsCount];//Final selected items for Knapsack
    int tempItems[itemsCount];// Temp selected items for Knapsack
   
    for (i = 0; i < sets; i++)
    {//Intial for loop to check all the permutations 
        //sets or resets the variable for each permutaions
        int weight = 0;
        int profit = 0;
        int k = 0;
        //sets the tempItems with -1
        for(k = 0; k<itemsCount; k++){
            tempItems[k] = -1;
        }        

        for (j = 0; j < itemsCount; j++)
        {// Inner for loop to check each item
            if (((i >> j) & 1) == 1) {
                //Calculates the weight and profit sum with the help of bit change to combine different combinantions only once
                weight += inventory->weight[j];
                profit += inventory->profit[j];
                //The respective items are added to temp Items
                tempItems[j] = j; 
            }  

            if (weight <= capacity && profit > profitSol)
            {// if the weight is less than or equal to capacity and profit is larger than already calculated profitsol,
             //then the new weight and profit sum is taken as final solution and respective item is added to final selectedItems.
                weightSol = weight;
                profitSol = profit;
                for(i = 0; i < itemsCount; i++){
                    selectedItems[i] = tempItems[i];
                }            
            }        
        }

    }

    // Required output is printed
    //First the total selected item
    printf("\n------------Total----------------\n");
    printf("weight = %d, profit = %d\n", weightSol, profitSol);
    //Second details of selected items
    printf("\n---------Selected item's---------\n");
    for(i = 0; i < itemsCount; i++){
        if(selectedItems[i]!=-1){
            printf("item %d, weight = %d, profit = %d\n", selectedItems[i]+1, inventory->weight[selectedItems[i]],
            inventory->profit[selectedItems[i]]);
        }
    }

    // Free's the memorey allocated to inventory struct
    free(inventory->weight);
    free(inventory->profit);
    free(inventory);
    return 0; 
}
