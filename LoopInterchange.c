/************************************************************
*       Author: Sri Jitendra Satpathy                       *
*       Last Modified: 3/12/2018                            *
************************************************************/


#include <stdio.h>
#include<time.h>
#define ROW 700
#define COL 700

float A[ROW][COL];
float B[ROW][COL];

/*Arrays to store the result after matrix multiplication.
  Results are later used to test if the interchanging loops has same result. */
float result1[ROW][COL];
float result2[ROW][COL];
float result3[ROW][COL];
float result4[ROW][COL];
float result5[ROW][COL];
float result6[ROW][COL];

//Declaring functions with different loop interchanging mechanisms.
void ijkMatrixMulOnHost(float M[ROW][COL], float N[ROW][COL], float P[ROW][COL], int width);
void ikjMatrixMulOnHost(float M[ROW][COL], float N[ROW][COL], float P[ROW][COL], int width);
void jikMatrixMulOnHost(float M[ROW][COL], float N[ROW][COL], float P[ROW][COL], int width);
void jkiMatrixMulOnHost(float M[ROW][COL], float N[ROW][COL], float P[ROW][COL], int width);
void kijMatrixMulOnHost(float M[ROW][COL], float N[ROW][COL], float P[ROW][COL], int width);
void kjiMatrixMulOnHost(float M[ROW][COL], float N[ROW][COL], float P[ROW][COL], int width);




int main()
{
    int i = 0,j = 0,test = 0;
    int init = 0;
    clock_t ijk,ikj,jik,jki,kij,kji;

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
            result4[i][j] = 0.0;
            result5[i][j] = 0.0;
            result6[i][j] = 0.0;
        }
    }
    printf("Load complete.\nComputing matrix multiplication using various loop interchanging mechanism.\n");

    //Calling the functions and calculating Matrix Multiplication performance.

    ijk = clock();
    ijkMatrixMulOnHost(A,B,result1,ROW);
    ijk = clock() - ijk;

    ikj = clock();
    ikjMatrixMulOnHost(A,B,result2,ROW);
    ikj = clock() - ikj;

    jik = clock();
    jikMatrixMulOnHost(A,B,result3,ROW);
    jik = clock() - jik;

    jki = clock();
    jkiMatrixMulOnHost(A,B,result4,ROW);
    jki = clock() - jki;

    kij = clock();
    kijMatrixMulOnHost(A,B,result5,ROW);
    kij = clock() - kij;

    kji = clock();
    kjiMatrixMulOnHost(A,B,result6,ROW);
    kji = clock() - kji;
	
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
            if(result5[i][j]!= result6[i][j]){
                printf("result5[%d][%d] != result6[%d][%d]\n",i,j,i,j);
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

    printf("==================================================================================\n");
    printf("         ijk         ikj             jik           jki           kij          kji     \n");
    printf("==================================================================================\n");
    printf("     %f      %f      %f      %f      %f      %f      \n",((double)ijk)/CLOCKS_PER_SEC,((double)ikj)/CLOCKS_PER_SEC,((double)jik)/CLOCKS_PER_SEC
                                                                    ,((double)jki)/CLOCKS_PER_SEC,((double)kij)/CLOCKS_PER_SEC,((double)kji)/CLOCKS_PER_SEC);
    printf("==================================================================================\n");

    
    return 0;
}

//Making functions for each loop interchanging type.

//Loop interchanging for ijk.
void ijkMatrixMulOnHost(float M[ROW][COL], float N[ROW][COL], float P[ROW][COL], int width){
    int i  = 0, j= 0, k = 0;
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
                printf("ijk: result1[%d][%d] : %f\n",i,j,P[i][j]);
            }
        }
    }
}

//Loop interchanging for ikj.
void ikjMatrixMulOnHost(float M[ROW][COL], float N[ROW][COL], float P[ROW][COL], int width){
    int i  = 0, j= 0, k = 0;
    float sum = 0, a = 0, b = 0;
    for(i = 0; i < width; i++){
        for(k = 0; k < width; k++){
                sum = 0;
            for(j = 0; j < width; j++){
                a = M[i][k];
                b = N[k][j];
                sum += a * b;
            }
            P[i][k] = sum;
            if(i == ROW - 10 && k == COL -20){
                printf("ikj: result2[%d][%d] : %f\n",i,k,P[i][k]);
            }
        }
    }
}

//Loop interchanging for jik.
void jikMatrixMulOnHost(float M[ROW][COL], float N[ROW][COL], float P[ROW][COL], int width){
    int i  = 0, j= 0, k = 0;
    float sum = 0, a = 0, b = 0;
    for(j = 0; j < width; j++){
        for(i = 0; i < width; i++){
                sum = 0;
            for(k = 0; k < width; k++){
                a = M[i][k];
                b = N[k][j];
                sum += a * b;
            }
            P[j][i] = sum;
            if(j == ROW - 10 && i == COL - 20){
                printf("jik: result3[%d][%d] : %f\n",j,i,P[j][i]);
            }
        }
    }
}

//Loop interchanging for jki.
void jkiMatrixMulOnHost(float M[ROW][COL], float N[ROW][COL], float P[ROW][COL], int width){
    int i  = 0, j= 0, k = 0;
    float sum = 0, a = 0, b = 0;
    for(j = 0; j < width; j++){
        for(k = 0; k < width; k++){
                sum = 0;
            for(i = 0; i < width; i++){
                a = M[i][k];
                b = N[k][j];
                sum += a * b;
            }
            P[j][k] = sum;
            if(j == ROW - 10 && k == COL - 20){
                printf("jki: result4[%d][%d] : %f\n",j,k,P[j][k]);
            }
        }
    }
}

//Loop interchanging for kij.
void kijMatrixMulOnHost(float M[ROW][COL], float N[ROW][COL], float P[ROW][COL], int width){
    int i  = 0, j= 0, k = 0;
    float sum = 0, a = 0, b = 0;
    for(k = 0; k < width; k++){
        for(i = 0; i < width; i++){
                sum = 0;
            for(j = 0; j < width; j++){
                a = M[i][k];
                b = N[k][j];
                sum += a * b;
            }
            P[k][i] = sum;
            if(k == ROW - 10 && i == COL - 20){
                printf("kij: result5[%d][%d] : %f\n",k,i,P[k][i]);
            }
        }
    }
}

//Loop interchanging for kji.
void kjiMatrixMulOnHost(float M[ROW][COL], float N[ROW][COL], float P[ROW][COL], int width){
    int i  = 0, j= 0, k = 0;
    float sum = 0, a = 0, b = 0;
    for(k = 0; k < width; k++){
        for(j = 0; j < width; j++){
                sum = 0;
            for(i = 0; i < width; i++){
                a = M[i][k];
                b = N[k][j];
                sum += a * b;
            }
            P[k][j] = sum;
            if(k == ROW - 10 && j == COL - 20){
                printf("kji: result6[%d][%d] : %f\n",k,j,P[k][j]);
            }
        }
    }
}
