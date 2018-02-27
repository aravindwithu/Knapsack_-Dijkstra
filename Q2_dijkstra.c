/*
Project 3 - dijkstra algorithm.​
By Aravind Venkit
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

//Intial global N - number of nodes for the garph
int N = 0;

/*
This Method os ussed to set the N value by geting the node count from the given file by counting number of columns in first line of thematrix text file.
*/
void setN(char fileName[]){
    //Initialize file
    FILE *file;
    //file open
    file = fopen(fileName, "r");
    // check whether the file is valid or not
    if(!file){
        fprintf(stderr, "Can't onpen the file %s", fileName);
    }

    char buf[100] = ""; 
    //buffer char array is used to buffer in the first line   
    while(fgets(buf, 100, file)){
        if(buf[strlen(buf)-1] == '\n'){
           buf[strlen(buf)-1] = '\0';
       }
       // the strtok is used to get the individual node items with ',' special char
        char *str = strtok(buf, ",");
        int i =0;
        while (str != NULL){
             str = strtok(NULL, ",");
             N++; // The number of node is incremented untill all nodes are takedn into account            
        }
        free(str);
        break;
   }
   // file close
   fclose(file);	 
}

/*
This methode Gets distance array as input and displays the respective items
*/
void DisplayDistance(int distance[]){
    int i = 0;
    printf("Node   Distance from source\n");
    for (i = 0; i < N; i++){
        if(distance[i] == INT_MAX){
            // if INT_MAX the distance not reachable i.e. Infinity
            printf("%2d \tInfinity\n", i+1);
        }
        else{
            // rest of the reachable minimum distance are printed here
            printf("%2d %10d\n", i+1, distance[i] );
        }
        
    }
}

/*
This function will intializes all the array variabls such as distance, visited, matrix
*/
void Init(int distance[], int visited[], int matrix[][N]){
    int i=0, j=0;
    for(i = 0; i < N; i++){
        distance[i] = INT_MAX, visited[i] = 0;
        for(j = 0; j < N; j++){
            matrix[i][j] = 0;
        }        
    }
}

/*
This function loads the given filename and stores the value into the matrix
*/
void LoadFile(char fileName[], int matrix[][N]){
    //Initializes the variables
    int i=0, j=0;
    //Initializes the file
    FILE *file;
    //file open
    file = fopen(fileName, "r");
    // given file is checked is valid or not
    if(!file){
        fprintf(stderr, "Can't onpen the file %s", fileName);
    }

    // fetches the data and stores the sane in matrix
    for(i = 0; i < N; i++){
        
        for(j = 0; j < N; j++){
            if(!fscanf(file, "%d,", &matrix[i][j])){
                break;
            }  
        }
    }

    //file close
    fclose(file);
}

int main(int argc, char *argv[])
{
    //Get file name as argument or take knapsack.txt as default file name
    char fileName[30];
    if(argv[1] == NULL){
        strcpy(fileName, "matrix_input.txt");
    }
    else{
        strcpy(fileName, argv[1]);
    }

    // setN is called to set the N
    setN(fileName);
    // Declaration of required arrays and matrix
    int distance[N];  // to store the minimum distance of the node from source node, Intialized with INT_MAX
    int visited[N];   // Visited nodes are marked as 1 and not visited are intialized to 0.        
    int matrix[N][N]; // to get the graph in matrix
    // Initialization of the arrays and matrix
    Init(distance,visited,matrix);
    // load file method is called
    LoadFile(fileName, matrix); 
    // sets the source node to 0 
    distance[0] = 0; 
    int n = 0;
    // while loop to loop all the nodes
    while (n < N){
        // variable initialization
        int i = 0, min = INT_MAX, minIndex;   
        // To select the minimum distance and respective index from the distance array     
        for (i = 0; i < N; i++){
            if (visited[i] == 0 && distance[i] <= min){
                min = distance[i], minIndex = i;
            }
        }
        // visited is true for selected minimum index
        visited[minIndex] = 1, n++;
        // to Identify the new minimum distance and store the same in distance array
        // Matrix values with -99. distance with Int_Max for minIndex are restricted.
        for (i = 0; i < N; i++){
            if (visited[i] == 0 && matrix[minIndex][i] != -99 && distance[minIndex] != INT_MAX 
                && distance[minIndex]+matrix[minIndex][i] < distance[i]){
                distance[i] = distance[minIndex] + matrix[minIndex][i];
            }
        }
    } 
    // display distance function is called.
    DisplayDistance(distance);
    return 0; 
}
