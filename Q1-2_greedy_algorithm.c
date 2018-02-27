/*
Project 3 - greedy algorithms for 0/1 knapsack.​
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
    int *itemNum;
    int *weight;
    int *profit;
    int *benefitPerUnit;
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
        inventory->itemNum = malloc( sizeof( int ) * itemsCount);
        inventory->weight = malloc( sizeof( int ) * itemsCount);
        inventory->profit = malloc( sizeof( int ) * itemsCount);
       }

       if(indx == 1){
        //The respective items weight are loaded to struct inventory.
        char *str = strtok(buf, ",");
        int i =0;
        for(i = 0; i<itemsCount; i++){
            inventory->itemNum[i] = i;
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
/*
Maximum benefit first, greedy algorithm which adds maximum profit items first to the knapsack.
*/
void MaxBenefitFirst(){
    //Intialization of the variables
    int i = 0, j = 0, temp = 0;
    int greedySol = 0;// the final total profit
    int greedyWeight = 0;// the final total weight
    int selectedItems[itemsCount]; // the final selected items

    // sorting the invetory array to the maximum profit order.
    for (i = 0; i < itemsCount; i++){
        for (j = i + 1; j < itemsCount; j++){
            if (inventory->profit[i]  < inventory->profit[j]){
                temp = inventory->profit[i];
                inventory->profit[i] = inventory->profit[j];
                inventory->profit[j] = temp;
                temp = inventory->weight[i];
                inventory->weight[i] = inventory->weight[j];
                inventory->weight[j] = temp;
                temp = inventory->itemNum[i];
                inventory->itemNum[i] = inventory->itemNum[j];
                inventory->itemNum[j] = temp;
            }
        }
    }

    // Adding the items to the knapsack from starting index of the sorted array and calculating the respective total weight and profit solution.
    for(i = 0; i<itemsCount; i++){ 
        selectedItems[i] = -1;
        if((greedyWeight + inventory->weight[i]) <= capacity){
            greedySol += inventory->profit[i];
            greedyWeight += inventory->weight[i];    
            selectedItems[i] = inventory->itemNum[i];                  
        }
    }

    // Required output is printed
    //First the total selected item
    printf("\n-----Max Benefit First Total-----\n");
    printf("weight = %d, profit = %d\n", greedyWeight, greedySol);
    //Second details of selected items
    printf("\n---------Selected item's---------\n");
    for(i = 0; i < itemsCount; i++){
        if(selectedItems[i]!=-1){
            printf("item %d, weight = %d, profit = %d\n", selectedItems[i]+1, inventory->weight[selectedItems[i]],
             inventory->profit[selectedItems[i]]);
        }
    }
}

/*
Minimum Weight First, greedy algorithm which adds minimum weight items first to the knapsack.
*/
void MinimumWeightFirst(){
    //Intialization of the variables
    int i = 0, j = 0, temp = 0;
    int greedySol = 0;// the final total profit
    int greedyWeight = 0;// the final total weight
    int selectedItems[itemsCount]; // the final selected items

    // sorting the invetory array to the minimum weight order.
    for (i = 0; i < itemsCount; i++){
        for (j = i + 1; j < itemsCount; j++){
            if (inventory->weight[i]  > inventory->weight[j]){
                temp = inventory->profit[i];
                inventory->profit[i] = inventory->profit[j];
                inventory->profit[j] = temp;
                temp = inventory->weight[i];
                inventory->weight[i] = inventory->weight[j];
                inventory->weight[j] = temp;
                temp = inventory->itemNum[i];
                inventory->itemNum[i] = inventory->itemNum[j];
                inventory->itemNum[j] = temp;
            }
        }
    }

    // Adding the items to the knapsack from starting index of the sorted array and calculating the respective total weight and profit solution.
    for(i = 0; i<itemsCount; i++){ 
        selectedItems[i] = -1;
        if((greedyWeight + inventory->weight[i]) <= capacity){
            greedySol += inventory->profit[i];
            greedyWeight += inventory->weight[i];  
            selectedItems[i] = inventory->itemNum[i];                   
        }
    }

    // Required output is printed
    //First the total selected item
    printf("\n----Minimum Weight First Total---\n");
    printf("weight = %d, profit = %d\n", greedyWeight, greedySol);
    //Second details of selected items
    printf("\n---------Selected item's---------\n");
    for(i = 0; i < itemsCount; i++){
        if(selectedItems[i]!=-1){
            printf("item %d, weight = %d, profit = %d\n", selectedItems[i]+1, inventory->weight[selectedItems[i]],
             inventory->profit[selectedItems[i]]);
        }
    }
}

/*
Max Weight First, greedy algorithm which adds max weight items first to the knapsack.
*/
void MaxWeightFirst(){
    //Intialization of the variables
    int i = 0, j = 0, temp = 0;
    int greedySol = 0;// the final total profit
    int greedyWeight = 0;// the final total weight
    int selectedItems[itemsCount]; // the final selected items

    // sorting the invetory array to the max weight order.
    for (i = 0; i < itemsCount; i++){
        for (j = i + 1; j < itemsCount; j++){
            if (inventory->weight[i]  < inventory->weight[j]){
                temp = inventory->profit[i];
                inventory->profit[i] = inventory->profit[j];
                inventory->profit[j] = temp;
                temp = inventory->weight[i];
                inventory->weight[i] = inventory->weight[j];
                inventory->weight[j] = temp;
                temp = inventory->itemNum[i];
                inventory->itemNum[i] = inventory->itemNum[j];
                inventory->itemNum[j] = temp;
            }
        }
    }

    // Adding the items to the knapsack from starting index of the sorted array and calculating the respective total weight and profit solution.
    for(i = 0; i<itemsCount; i++){ 
        selectedItems[i] = -1;
        if((greedyWeight + inventory->weight[i]) <= capacity){
            greedySol += inventory->profit[i];
            greedyWeight += inventory->weight[i];  
            selectedItems[i] = inventory->itemNum[i];                 
        }
    }

    // Required output is printed
    //First the total selected item
    printf("\n-----Max Weight First Total------\n");
    printf("weight = %d, profit = %d\n", greedyWeight, greedySol);
    //Second details of selected items
    printf("\n---------Selected item's---------\n");
    for(i = 0; i < itemsCount; i++){
        if(selectedItems[i]!=-1){
            printf("item %d, weight = %d, profit = %d\n", selectedItems[i]+1, inventory->weight[selectedItems[i]],
             inventory->profit[selectedItems[i]]);
        }
    }
}

/*
Maximum Benefit Per Unit, greedy algorithm which adds Maximum Benefit Per Unit items first to the knapsack.
*/
void MaximumBenefitPerUnit(){
    //Intialization of the variables
    int i = 0, j = 0, temp = 0;
    int greedySol = 0;// the final total profit
    int greedyWeight = 0;// the final total weight
    int selectedItems[itemsCount]; // the final selected items
    //Memorey allocation for benefit Per Unit in inventory
    inventory->benefitPerUnit = malloc( sizeof( int ) * itemsCount);

    // sorting the invetory array to the Maximum Benefit Per Unit order.
    for (i = 0; i < itemsCount; i++){
        for (j = i + 1; j < itemsCount; j++){
            // benefitPerUnit are calculated as required for sorting
            inventory->benefitPerUnit[i] = inventory->profit[i]/inventory->weight[i];
            inventory->benefitPerUnit[j] = inventory->profit[i]/inventory->weight[i];
            if (inventory->benefitPerUnit[i]  < inventory->benefitPerUnit[j]){
                temp = inventory->profit[i];
                inventory->profit[i] = inventory->profit[j];
                inventory->profit[j] = temp;
                temp = inventory->weight[i];
                inventory->weight[i] = inventory->weight[j];
                inventory->weight[j] = temp;
                temp = inventory->itemNum[i];
                inventory->itemNum[i] = inventory->itemNum[j];
                inventory->itemNum[j] = temp;
                temp = inventory->benefitPerUnit[i];
                inventory->benefitPerUnit[i] = inventory->benefitPerUnit[j];
                inventory->benefitPerUnit[j] = temp;
            }
        }
    }

    // Adding the items to the knapsack from starting index of the sorted array and calculating the respective total weight and profit solution.
    for(i = 0; i<itemsCount; i++){ 
        selectedItems[i] = -1;
        if((greedyWeight + inventory->weight[i]) <= capacity){
            greedySol += inventory->profit[i];
            greedyWeight += inventory->weight[i]; 
            selectedItems[i] = inventory->itemNum[i];                    
        }
    }
    // Required output is printed
    //First the total selected item
    printf("\n--Maximum Benefit Per UnitTotal--\n");
    printf("weight = %d, profit = %d\n", greedyWeight, greedySol);
    //Second details of selected items
    printf("\n---------Selected item's---------\n");
    for(i = 0; i < itemsCount; i++){
        if(selectedItems[i]!=-1){
            printf("item %d, weight = %d, profit = %d\n", selectedItems[i]+1, inventory->weight[selectedItems[i]],
             inventory->profit[selectedItems[i]]);
        }
    }
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
    
    // Respective functions are called to execute each greedy algorithm.
    MaxBenefitFirst();
    MinimumWeightFirst();
    MaxWeightFirst();
    MaximumBenefitPerUnit();

    // Free's the memorey allocated to inventory struct
    free(inventory->itemNum);
    free(inventory->weight);
    free(inventory->profit);
    free(inventory->benefitPerUnit);
    free(inventory);
    return 0; 
}
