/************************************************************
*       Author: Sri Jitendra Satpathy                       *
*       Last Modified: 3/12/2018                            *
************************************************************/


#include <stdio.h>
#include<time.h>
#define ROW 1000
#define COL 1000

float A[ROW][COL];
float B[ROW][COL];

/*Arrays to store the result after matrix multiplication.
  Results are later used to test if the unrolling loops has same result. */
float result1[ROW][COL];
float result2[ROW][COL];
float result3[ROW][COL];

//Declaring the functions with different unrolling values.
void noUnrollMatMul(float M[ROW][COL],float N[ROW][COL],float P[ROW][COL],int width);
void UnrollByFourMatMul(float M[ROW][COL],float N[ROW][COL],float P[ROW][COL],int width);
void UnrollByEightMatMul(float M[ROW][COL],float N[ROW][COL],float P[ROW][COL],int width);


int main()
{
    int i = 0,j = 0;
    int init = 0;
    int test =  1;
    clock_t c1,c2,c3;

    //Initializing the arrays with random numbers.
    printf("Loading matrices A and B with random values.\n");
    for (i=0;i<ROW;i++){
		for (j=0;j<COL;j++){
			init=3125*init%65536;
			A[i] [j]=(init-32768.0)/16384.0;
			init=3125*init%65536;
			B[i] [j]= (init-32768.0)/16384.0;
            result1[i][j] = 0.0;
            result2[i][j] = 0.0;
            result3[i][j] = 0.0;
        }
    }
    printf("Load complete.\nComputing matrix multiplication using various loop unrolling mechanism.\n");

    c1 = clock();
    noUnrollMatMul(A,B,result1,ROW);
    c1 = clock() - c1;
    c2 = clock();
    UnrollByFourMatMul(A,B,result2,ROW);
    c2 = clock() - c2;
    c3 = clock();
    UnrollByEightMatMul(A,B,result3,ROW);
    c3 = clock() - c3;

    //Testing if the unrolling produces same result.
    printf("Comparing all the matrices for equality.\n");
    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            if(result1[i][j]!= result2[i][j]){
                printf("result 1 and result 2 are not same\n");
                i = j = 2000;
                test = 0;
                break;
            }
            if(result2[i][j]!= result3[i][j]){
                printf("result 2 and result 3 are not same\n");
                i = j = 2000;
                test = 0;
                break;
            }
        }
    }

    if(test == 0){
        printf("Matrices are not equal!\nMake sure the matrix width is a multiple of both 4 and 8!\n");
    }else{
        printf("All the matrices are equal!\n");
    }

    //Printing out performance results.
    printf("===============================================================\n");
    printf("         No Unroll         Unroll By 4             Unroll By 8 \n");
    printf("===============================================================\n");
    printf("         %f          %f                %f \n",((float)c1)/CLOCKS_PER_SEC,((float)c2)/CLOCKS_PER_SEC,((float)c3)/CLOCKS_PER_SEC);
    printf("===============================================================\n");

    return 0;
}

void noUnrollMatMul(float M[ROW][COL],float N[ROW][COL], float P[ROW][COL], int width){
    int i = 0, j = 0, k = 0;
    float sum = 0, a = 0, b = 0;
    for(i = 0; i < width; i++){
        for(j = 0; j < width; j++){
                sum = 0;
            for(k = 0; k < width; k++){
                a = M[i][k];
                b = N[k][j];
                sum += a * b;
            }
        P[i][j] = sum;
        if(i == ROW - 10 && j == COL - 20){
            printf("result1[%d][%d]: %f\n",i,j,P[i][j]);
        }
        }
    }
}

/* Unroll any number only works if the array size is the multiple of that number. Else, it produces different results.
   Need to confirm this theory with professor. */

void UnrollByFourMatMul(float M[ROW][COL],float N[ROW][COL], float P[ROW][COL], int width){
    int i = 0, j = 0, k = 0;
    float sum = 0, a = 0, b = 0;
    for(i = 0; i < width; i++){
        for(j = 0; j < width; j++){
                sum = 0;
            for(k = 0; k < width; k = k+4){
                a = M[i][k];
                b = N[k][j];
                sum += a * b;

                a = M[i][k+1];
                b = N[k+1][j];
                sum += a * b;

                a = M[i][k+2];
                b = N[k+2][j];
                sum += a * b;

                a = M[i][k+3];
                b = N[k+3][j];
                sum += a * b;
            }
        P[i][j] = sum;
        if(i == ROW - 10 && j == COL - 20){
            printf("result2[%d][%d]: %f\n",i,j,P[i][j]);
        }
        }
    }
}

void UnrollByEightMatMul(float M[ROW][COL],float N[ROW][COL], float P[ROW][COL], int width){
    int i = 0, j = 0, k = 0;
    float sum = 0, a = 0, b = 0;
    for(i = 0; i < width; i++){
        for(j = 0; j < width; j++){
                sum = 0;
            for(k = 0; k < width; k = k+8){
                a = M[i][k];
                b = N[k][j];
                sum += a * b;

                a = M[i][k+1];
                b = N[k+1][j];
                sum += a * b;

                a = M[i][k+2];
                b = N[k+2][j];
                sum += a * b;

                a = M[i][k+3];
                b = N[k+3][j];
                sum += a * b;
                a = M[i][k+4];
                b = N[k+4][j];
                sum += a * b;

                a = M[i][k+5];
                b = N[k+5][j];
                sum += a * b;

                a = M[i][k+6];
                b = N[k+6][j];
                sum += a * b;

                a = M[i][k+7];
                b = N[k+7][j];
                sum += a * b;
            }
        P[i][j] = sum;
        if(i == ROW - 10 && j == COL - 20){
            printf("result3[%d][%d]: %f\n",i,j,P[i][j]);
        }
        }
    }
}
