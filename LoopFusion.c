/************************************************************
*       Author: Sri Jitendra Satpathy                       *
*       Last Modified: 3/14/2018                            *
************************************************************/

#include<stdio.h>
#include<time.h>
#define ROW 3000
#define COL 3000

//Declaration of the arrays has to be global because C does not allow large sized arrays to be declared in a method.
//Reference:https://stackoverflow.com/questions/3771154/how-to-declare-and-use-huge-arrays-of-1-billion-integers-in-c
float A [ROW][COL];
float B [ROW][COL];
float C [ROW][COL];
float D [ROW][COL];

//Declaration of the functions.
void withOutLoopFusion(float M[ROW][COL],float N[ROW][COL]);
void withLoopFusion(float M[ROW][COL],float N[ROW][COL]);

int main() {

	int i = 0, j = 0, test = 0;
	int init = 1325;
	clock_t c1,c2;

	//Filling up the arrays with random values between 0 and 1;
	printf("Loading the matrices with random values!\n");
	for (i=0;i<ROW;i++){
		for (j=0;j<COL;j++){
			init=3125*init%65536;
			A[i] [j]=(init-32768.0)/16384.0;
			C[i] [j] =A[i][j];
			init=3125*init%65536;
			B[i] [j]= (init-32768.0)/16384.0;
			D[i][j] = B[i] [j] ;
			//Printing out random array location to see if arrays have same values
			if(i == ROW - 1 && j == COL - 10) {
                printf("A[%d][%d] = %f\tB[%d][%d] = %f\tC[%d][%d] = %f\tD[%d][%d]=%f\n",i,j,A[i][j],i,j,B[i][j],i,j,C[i][j],i,j,D[i][j]);
			}

		}
	}
	printf("Loading complete.\n");

	//Recording the performance of loops before and after applying loop fusion.
	c1 = clock();
	withOutLoopFusion(A,B);
	c1 = clock() - c1;
	c2 = clock();
	withLoopFusion(C,D);
	c2 = clock() - c2;

	//Checking the semantics of the of the program before and after loop transformation.
	for(j = 2; j < COL - 1 ; j++ ) {
	  for (i = 2; i < ROW - 1; i++) {
		if(A[i][j] != C[i][j]) {
			test = 1;
			printf("A[%d][%d] != C[%d][%d]\n",i,j,i,j);
			i=j=10000;
            break;
			}
		if(B[i][j] != D[i][j]) {
			test = 1;
			printf("B[%d][%d] != D[%d][%d]\n",i,j,i,j);
			printf("%f\t%f",B[i][j],D[i][j]);
			i=j=10000;
            break;
			}
		}
	}

	//Printing if the arrays are same or not.
	if(test == 1){
		printf("Arrays are not same!\n");
	}else{
		printf("Arrays are same!\n");
	}
	//Printing out the time performance of loop before and after loop fusion.
	printf("==============================================================\n");
	printf("	Before Loop Fusion\t\tAfter Loop Fusion\n");
	printf("==============================================================\n");
	printf("\t\t%f\t\t%f",((double)c1)/CLOCKS_PER_SEC,((double)c2)/CLOCKS_PER_SEC);

	return 0;
}


void withOutLoopFusion(float M[ROW][COL],float N[ROW][COL]){
	int i = 0, j = 0;

	//Running the loops separately.
	for (j = 2 ; j < ROW - 1; j++ ) {
	   for (i = 2; i < ROW - 1; i++ ) {
		   M[i] [j] = 0.25 *  (N[i-1][j] + N [i+1] [j] + N [i] [j-1] + N [i] [j+1] );
	   }
	}

	for (j = 2 ; j < ROW - 1; j++ ) {
	   for (i = 2; i < ROW - 1; i++ ) {
	   N[i][j] = M[i] [j];
		}
	}

}

void withLoopFusion(float M[ROW][COL],float N[ROW][COL]){
	int i = 0, j = 0;

	//Applying loop peeling and loop shifting to fuse the loops.
	for(i = 2 ; i < ROW - 1 ; i++ ) {
		M[i][2] = 0.25 * (N[i-1] [2] + N[i+1] [2] + N[i][1]+ N[i] [3] ) ;
	}

	for (j = 2 ; j < COL - 1 ; j++) {
	   M[2][j] = 0.25 * (N[1] [j] + N[3] [j] + N[2][j-1]+ N[2] [j+1] ) ;
	}

	for(j = 2; j < COL - 2 ; j++ ) {
	  for (i = 2; i < ROW - 2; i++) {
	   M[i+1][j+1] = 0.25 * (N[i][j+1] + N[i+2][j+1] + N[i+1] [j] + N[i+1] [j+2] ) ;
	   N[i][j] = M[i][j];
		}
	}
	for(j = 2 ; j < COL - 1 ; j++) {
	 N[ROW - 2][j] = M[ROW - 2][j] ;
	}

	for(i = 2 ; i < ROW - 1 ; i++) {
	 N[i][COL - 2] = M[i][COL - 2] ;
	}
}
