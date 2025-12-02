#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) >= (b) ? (a) : (b))

//Define the size of the triangle
#define N 9

//the function coin returns the maximum number of possible coins and prints the path along the way.
//level represents what row the first element of a triangle is.

long coin(int**arr , int n , unsigned char* path){



//first we split the triangle into two halves, the left and the right.

int ** arrLEFT = malloc( (n-1) * sizeof(int*));//points the the head of the left triangle
if(arrLEFT == NULL){
    fprintf(stderr,"Failed to allocate memory");
    exit(1);
}
for (int i = 0; i < n - 1; i++) {
    arrLEFT[i] = malloc((i + 1) * sizeof(int));
    if(arrLEFT[i] == NULL){
    fprintf(stderr,"Failed to allocate memory");
    exit(1);
    }    
}


int ** arrRIGHT = malloc( (n-1) * sizeof(int*)); //points to the head of the right triangle
if(arrRIGHT == NULL){
    fprintf(stderr,"Failed to allocate memory");
    exit(1);
}
for (int i = 0; i < n - 1; i++) {
    arrRIGHT[i] = malloc((i + 1) * sizeof(int)); // row i has i+1 elements
    if(arrRIGHT[i] == NULL){
        fprintf(stderr,"Failed to allocate memory");
        exit(1);
    }
}


//set the values of the left triangle based on the main triangle, starting from (1,0) if (0,0) is the starting point of the original
for(int i = 0 ; i < n - 1 ; i++){ 
    for(int j = 0 ; j <= i ; j++ ){
        arrLEFT[i][j] = arr[i + 1][j];
    }
}
//same for the right triangle
for(int i = 0 ; i < n - 1 ; i++ ){
    for(int j = 0 ; j <= i ; j++){
        arrRIGHT[i][j] = arr[i+1][j+1];
    }
}


unsigned char  * pathLEFT = malloc( n * sizeof(unsigned char)); //n-1 bits for a n row triangle, + 1 placeholder
if(pathLEFT == NULL){
    fprintf(stderr,"Failed to allocate memory");
    exit(1);
}
unsigned char  * pathRIGHT = malloc( n * sizeof(unsigned char));
if(pathRIGHT == NULL){
    fprintf(stderr,"Failed to allocate memory");
    exit(1);
}

long result; //for the numerical best sum
long resultleft; //for the numerical best sum of the left triangle
long resultright; //..and for the right triangle

if(n == 2){ //the base of reccursion
    resultleft = arrLEFT[0][0] + arr[0][0]; 
    resultright = arrRIGHT[0][0] + arr[0][0];    
} else{ //reccursion
    resultleft = coin(arrLEFT , n-1, pathLEFT ) + arr[0][0];
    resultright = coin(arrRIGHT , n-1, pathRIGHT) + arr[0][0] ;
}


result = MAX( resultleft , resultright );

//0 represents turning left, while 1 represents turning right
if(n == 2){ //for n=2 the left and right paths dont exist, so we fill them in.
pathLEFT[0] = '-'; 
pathRIGHT[0] = '-';
path[0] = '-';

    if (resultleft == result){
        path[1]=0;
    } else {
        path[1]=1;
    }

} else if(resultleft == result){
    
    pathLEFT[n-1] = 0; //whenever n>2 the index muse be 
    
    for (int i = 0; i < n; i++) {
        path[i] = pathLEFT[i];
    }
    
} else {

    pathRIGHT[n-1] = 1;

    for (int i = 0; i < n; i++) {
        path[i] = pathRIGHT[i];
    }
    
}

//Now we free the memory that we used:
free(pathRIGHT);
free(pathLEFT);

for (int i = 0; i < n-1; i++) {
    free(arrLEFT[i]);
}
free(arrLEFT);

for (int i = 0; i < n-1; i++) {
    free(arrRIGHT[i]);
}
free(arrRIGHT);


return result;



}



int main() {
    int n = N; // number of rows
    int **arr = malloc(n * sizeof(int*)); // array of pointers/arrays
    if(arr == NULL){
    fprintf(stderr,"Failed to allocate memory");
    exit(1);
}
    // Allocate each row
for (int i = 0; i < n; i++) {
    arr[i] = malloc((i + 1) * sizeof(int)); // row i has i+1 elements
    if(arr[i] == NULL){
        fprintf(stderr,"Failed to allocate memory");
        exit(1);
    }
}

    /* Fill the array with some values
    int value = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            arr[i][j] = value++;
        }
    }*/

int data[9][9] = {
    {0}, 
    {1, 6}, 
    {3, 5, 1}, 
    {15, 3, 8, 2}, 
    {1, 2, 1, 6, 4}, 
    {4, 1, 2, 6, 3, 7}, 
    {10, 8, 17, 2, 7, 8, 4}, 
    {7, 2, 10, 7, 8, 4, 2, 6}, 
    {14, 4, 6, 8, 4, 7, 6, 7, 10}
};

    for(int i = 0 ; i < n ; i++){ 
        for(int j = 0 ; j <= i ; j++ ){
            arr[i][j] = data[i][j];
        }
    }



    //Print the array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    unsigned char path[N]; //the path of a N row triangle can be represented with a N-1 bit sequence.
    long coins = coin(arr,n,path);

    printf("the maximum ammount of coins is: %ld\n",coins);
    printf("Path: ");
    for (int i = n-1; i > 0 ; i--) {
        printf("%d", path[i]);
    }
    printf("\n");

    // Free memory
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}






