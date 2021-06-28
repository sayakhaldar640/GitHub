#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int sudoku[9][9]; // 2D array
int arr[580]; 

void printSudoku(int sudoku[9][9])
{
	int i , j;
	printf("\n\nThe solution is: \n\n");
	for(i = 1 ; i <= 9 ; i++)
	{
		for(j = 1 ; j <= 9 ; j++)
			printf("%d ",sudoku[i][j]);
		printf("\n");
	}
}


void createArray(int sudoku[9][9])
{
	int i , j , k , count = 0 , ec;
	for(i = 1 ; i <= 9 ; i++)
	{
		for(j = 1 ; j <= 9 ; j++)
		{
			if(sudoku[i][j] == 0)
				count++;
		}
	}
	
	ec = count * 9; // ec = element count
	for(i = 1 ; i <= ec ; i++)
		arr[i] = ((i-1) % 9) + 1;

	//for(i = 1 ; i <= ec ; i++)
		//printf("%d ",arr[i]); // Testing purpose
}

int rowCheck(int sudoku[9][9] , int arr[])
{
	
}
int main()
{
	int i , j;
	//clock_t start , end;
	//double tt;
	
	printf("Enter the sudoku puzzle: \n\n");
	for(i = 1 ; i <= 9 ; i++)
		for(j = 1 ; j <= 9 ; j++)
			scanf("%d",&sudoku[i][j]);
	
	//start = clock();
	printSudoku(sudoku);
	printf("\n\n\n");
	createArray(sudoku);
	//end = clock();
	
	//tt = ((double)(end-start)/CLOCKS_PER_SEC);
	//printf("\n\n TT = %f",tt);
	
	return 0;
}
