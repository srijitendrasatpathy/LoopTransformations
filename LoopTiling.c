/************************************************************
*       Author: Sri Jitendra Satpathy                       *
*       Last Modified: 3/14/2018                            *
************************************************************/

#include<stdio.h>
#include<time.h>
#define MIN(a,b) ((a) < (b)? a : b) //Defining min  function to be used in tiling mechanism
#define ROW 1000
#define COL 1000

//Declaring all the Arrays.
float A[ROW][COL];
float B[ROW][COL];

float result1[ROW][COL];
float result2[ROW][COL];
float result3[ROW][COL];
float result4[ROW][COL];
float result5[ROW][COL];

int counter = 2; //Just to make displaying prettier.

//Declaring all the required functions.
void withOutTile(float M[ROW][COL],float N[ROW][COL],float P[ROW][COL]);
void withTile(float M[ROW][COL],float N[ROW][COL],float P[ROW][COL], int tileValue);

int main() {
    int i = 0, j = 0,test = 0;
    clock_t c1,c2,c3,c4,c5;
    int init = 1325;

    //Filling the matrices with random values.
    printf("Loading matrices A and B with random values.\n");
    for (i = 0;i < ROW;i++){
      for (j = 0;j < COL;j++){
        init=3125*init%65536;
        A[i][j]=(init - 32768.0)/16384.0;
        init=3125*init%65536;
        B[i][j]= (init - 32768.0)/16384.0;
        result1[i][j] = 0;
        result2[i][j] = 0;
        result3[i][j] = 0;
        result4[i][j] = 0;
        result5[i][j] = 0;
        }
    }
    printf("Load complete.\nComputing matrix multiplication using loop tiling mechanism with various tile values.\nPlease provide at least a minute before you are able to see the result.\n");

    //Calling the functions and calculating the performance.
    c1 = clock();
    withOutTile(A,B,result1);
    c1 = clock() - c1;
    c2 = clock();
    withTile(A,B,result2,4);
    c2 = clock() - c2;
    c3 = clock();
    withTile(A,B,result3,8);
    c3 = clock() - c3;
    c4 = clock();
    withTile(A,B,result4,16);
    c4 = clock() - c4;
    c5 = clock();
    withTile(A,B,result5,32);
    c5 = clock() - c5;

    //Checking if the matrix multiplication result is same across all loop interchanges.
    printf("Comparing all the matrices for equality.\n");
    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            if(result1[i][j]!= result2[i][j]){
                printf("result1[%d][%d] != result2[%d][%d]\n",i,j,i,j);
				test = 1;
                i = j = 2000;
                break;
            }
            if(result2[i][j]!= result3[i][j]){
                printf("result2[%d][%d] != result3[%d][%d]\n",i,j,i,j);
				test = 1;
                i = j = 2000;
                break;
            }
            if(result3[i][j]!= result4[i][j]){
                printf("result3[%d][%d] != result4[%d][%d]\n",i,j,i,j);
				test = 1;
                i = j = 2000;
                break;
            }
            if(result4[i][j]!= result5[i][j]){
                printf("result4[%d][%d] != result5[%d][%d]\n",i,j,i,j);
				test = 1;
                i = j = 2000;
                break;
            }
        }
    }
	if(test == 1){
		printf("Matrices are not equal\n");
	}else{
		printf("All the matrices are equal!\n");
	}

    //Printing out the performance results.
    printf("==================================================================================\n");
    printf("No tile\t\tTile 4\t\tTile 8\t\tTile 16\t\tTile 32\n");
    printf("==================================================================================\n");
    printf("%f\t%f\t%f\t%f\t%f\n",((double)c1)/CLOCKS_PER_SEC,((double)c2)/CLOCKS_PER_SEC,((double)c3)/CLOCKS_PER_SEC
                                 ,((double)c4)/CLOCKS_PER_SEC,((double)c5)/CLOCKS_PER_SEC);

    return 0;
}

void withOutTile(float M[ROW][COL],float N[ROW][COL],float P[ROW][COL]){

    int i = 0, j = 0, k = 0;
    float sum = 0, a = 0, b = 0;

    //Calculating matrix multiplication the usual way.
    for (i = 0; i < ROW; i++) {
      for(j = 0; j < COL; j++) {
            sum = 0;
            for (k = 0; k < ROW; ++k) {
                a = M[i] [k];
                b = N[k] [j];
               sum += a * b;
            }
            P[i] [j] = sum;
            //Printing the value 800 because it is the value divisible by 4, 8,16 and 32
            if(i == 800 && j == 800){
                printf("result1[%d][%d]:%f\n",i,j,P[i][j]);
            }
        }
    }
}
void withTile(float M[ROW][COL],float N[ROW][COL],float P[ROW][COL], int tileValue){
    int i = 0, j = 0, k = 0;
    int ii = 0, jj = 0, kk = 0;
    float a = 0, b = 0;

    //Applying loop tiling.
    for (i = 0; i < ROW; i = i + tileValue) {
        for(j = 0; j < ROW; j = j + tileValue) {
            for (k = 0; k < ROW; k = k + tileValue) {
                for (ii = i; ii < MIN(i + tileValue,ROW); ii++ )
                   for (jj = j; jj < MIN(j + tileValue,ROW);jj++)
                     for(kk = k; kk < MIN(k + tileValue,ROW);kk++) {
                         a = A[ii] [kk];
                         b = B[kk] [jj];
                         P[ii][jj] += a*b;
                     }
            }
            //Print doesn't work. Need to check why!!
            //Probably because of i + tileValue.  It is possible that it skips the print.
            //Need to find a common divisor for 4,8,16,32 to print the result Ans: 800
            if(i == 800 && j == 800){
                printf("result%d[%d][%d]:%f\n",counter++,i,j,P[i][j]);
            }
        }
    }
}
