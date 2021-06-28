#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Global declaration
int puzzle[9][9];
int ch[9][9][9]; // choice array

/* Creation of choice array. For first element in puzzle array
	i.e position (1,1) we placed values 1 to 9 in ch[1][1][k] (k <- 1 to 9)
	similarly for position (5,6) in puzzle array values are placed in 
	ch[5][6][k] (k <- 1 to 9) and so on */ 
void createChoiceArray()
{
	int i , j , k;
	for(i = 1 ; i <= 9 ; i++)
		for(j = 1 ; j <= 9 ; j++)
			for(k = 1 ; k <= 9 ; k++)
				ch[i][j][k] = k;
}

/* Finds the numbers in the same row and
	dismisses those numbers from respective choice array position for ACO process*/

int setRowChoice(int i , int j)
{
    int k;

	for(k = 1 ; k <= 9 ; k++)
        if(puzzle[i][k] != 0)
            ch[i][j][puzzle[i][k]] = 0;
    
	return 0;
}

/* Finds the numbers in the same colomn and
	dismisses those numbers from respective choice array position for ACO process*/

int setColumnChoice(int i , int j)
{
    int k;

    for(k = 1 ; k <= 9 ; k++)
        if(puzzle[k][j] != 0)
            ch[i][j][puzzle[k][j]] = 0;
    
	return 0;
}

/* Finds the numbers in the same 3*3 grid and
	dismisses those numbers from respective choice array position for ACO process*/
int setGridChoice(int i , int j) 
{
	int k;
	int rowStart = (((i-1)/3)*3)+1;
	int colStart = (((j-1)/3)*3)+1;

	for(k = 1 ; k <= 9 ; k++)
		if(puzzle[rowStart + ((k-1)%3)][colStart + ((k-1)/3)] != 0)
			ch[i][j][puzzle[rowStart + ((k-1)%3)][colStart + ((k-1)/3)]] = 0;
	
	return 0;
}

/* if for a row in choice array all the values are 0 except one 
	set the value in corresponding puzzle array position*/
	 
int solvePuzzle()
{
    int i , j , k , totalZero , setChoice , setflag = 0;
    
	for(i = 1 ; i <= 9 ; i++)
	{
        for(j = 1 ; j <= 9 ; j++)
		{
            if(puzzle[i][j] == 0)
			{
            	totalZero = 0;
            	for(k = 1 ; k <= 9 ; k++)
				{
                	if(ch[i][j][k] == 0)
                    	totalZero++;
                	if(ch[i][j][k] != 0)
                    	setChoice=ch[i][j][k];
            	}
            	if(totalZero == 8) //when total no of possibilities is one
				{
                	puzzle[i][j] = setChoice; // setchoice is the unique value left for the unassigned box in the puzzle
                	setflag = 1;
        		}
        	}
        }
    }
    
    return setflag;
}

// Finds the unsolved position in puzzle array
int isSolve()
{
    int i , j;
    for(i = 1 ; i <= 9 ; i++)
        for(j = 1 ; j <= 9 ; j++)	
			if(puzzle[i][j] == 0)
                return 1;
    return 0;
}

/* Searches the grid to find an entry that is still unassigned. If
   found, the reference parameters row, col will be set the location
   that is unassigned, and true is returned. If no unassigned entries
   remain, false is returned. */
bool FindUnassignedLocation(int puzzle[9][9], int &row, int &col)
{
    for (row = 1 ; row <= 9 ; row++)
        for (col = 1; col <= 9 ; col++)
            if (puzzle[row][col] == 0)
                return true;
    
	return false;
}

/* Returns a boolean which indicates whether an assigned entry
   in the specified row matches the given number. */
bool UsedInRow(int puzzle[9][9], int row, int num)
{
    for (int col = 1 ; col <= 9 ; col++)
        if (puzzle[row][col] == num)
            return true;
    
	return false;
}

/* Returns a boolean which indicates whether an assigned entry
   in the specified column matches the given number. */
bool UsedInCol(int puzzle[9][9], int col, int num)
{
    for (int row = 1 ; row <= 9 ; row++)
        if (puzzle[row][col] == num)
            return true;
    
	return false;
}

/* Returns a boolean which indicates whether an assigned entry
   within the specified 3x3 box matches the given number. */
bool UsedInBox(int puzzle[9][9], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 1 ; row <= 3 ; row++)
        for (int col = 1 ; col <= 3 ; col++)
            if (puzzle[row+boxStartRow-1][col+boxStartCol-1] == num)
                return true;
    
	return false;
}

/* Returns a boolean which indicates whether it will be legal to assign
   num to the given row,col location. */
bool isSafe(int puzzle[9][9], int row, int col, int num)
{
    /* Check if 'num' is not already placed in current row,
       current column and current 3x3 box */
    return !UsedInRow(puzzle, row, num) &&
           !UsedInCol(puzzle, col, num) &&
           !UsedInBox(puzzle, row - ((row-1)%3), col - ((col-1)%3), num)&&
            puzzle[row][col]==0;
}

bool SolveSudoku(int puzzle[9][9])
{
    int row, col, num , k;
    // If there is no unassigned location, we are done
    if (!FindUnassignedLocation(puzzle, row, col))
       return true; // success!

    // consider digits 1 to 9
    for(k = 1 ; k <= 9 ; k++)
    {
        if(ch[row][col][k] != 0)
		{
            num = ch[row][col][k];
        	// if looks promising
        	if (isSafe(puzzle, row, col, num))
        	{
            	// make tentative assignment
            	puzzle[row][col] = num;

            	// return, if success, yay!
            	if (SolveSudoku(puzzle))
                	return true;

            	// failure, unmake & try again
            	puzzle[row][col] = 0;
        	}
        }
    }
    return false; // this triggers backtracking
}

// For printing the solved puzzle
int printPuzzle()
{
    int i , j;
    printf("\nPuzzle Solved -\n");
    printf("----------------\n");
    printf("----------------\n");
    for(i = 1 ; i <= 9 ; i++)
	{
        printf("\n");
        for(j = 1 ; j <= 9 ; j++)
            printf("%d ",puzzle[i][j]);
    }
}

int main()
{
    int i , j , k , iterate;
    clock_t start , end;
	double tt;
	
	for(i = 1 ; i <= 9 ; i++)
        for(j = 1 ; j <= 9 ; j++)
            scanf("%d",&puzzle[i][j]);
	
	start = clock();
    
	createChoiceArray(); // Creation of choice array
    while(isSolve()) // reducing possibilities and set values where find unique possibility 
	{
    	for(i=1;i<10;i++)
		{
        	for(j=1;j<10;j++)
			{
            	if(puzzle[i][j]==0)
				{
                	setRowChoice(i,j);
                	setColumnChoice(i,j);
                	setGridChoice(i,j);
            	}
        	}
    	}
    	iterate = solvePuzzle(); // Solving By ACO 
    	
		if(iterate == 0) // stops the while loop from going into infinite loop
        	break;
    }
    if(isSolve())
        SolveSudoku(puzzle); // Solving by backtracking method
    printPuzzle(); // prints the solved puzzle
    
	end = clock();
	
	tt = ((double)(end-start)/CLOCKS_PER_SEC);
	printf("\n\nTT = %f",tt);
	
    return 0;
}
