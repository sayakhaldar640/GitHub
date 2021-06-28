#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int puzzle[9][9];  // Sudoku puzzle
int ph[9][9][9]; // pheromone array

/* Creation of pheromone array. For first element of puzzle array
	i.e position (1,1) we placed values 1 to 9 in ph[1][1][k] (k <- 1 to 9)
	similarly for position (5,6) of puzzle array corresponding values are placed in 
	ph[5][6][k] (k <- 1 to 9) and so on */ 
void createPheromoneArray()
{
	int i , j , k;
	
	for(i = 1 ; i <= 9 ; i++)
		for(j = 1 ; j <= 9 ; j++)
			for(k = 1 ; k <= 9 ; k++)
				ph[i][j][k] = k;
}

/* Finds the numbers in the same row and
	dismisses those numbers from respective pheromone array position for ATM*/
int setRowChoice(int i , int j)
{
    int k;

	for(k = 1 ; k <= 9 ; k++)
        if(puzzle[i][k] != 0)
            ph[i][j][puzzle[i][k]] = 0;
    return 0;
}

/* Finds the numbers in the same colomn and
	dismisses those numbers from respective pheromone array position for ATM*/
int setColumnChoice(int i , int j)
{
    int k;

    for(k = 1 ; k <= 9 ; k++)
        if(puzzle[k][j] != 0)
            ph[i][j][puzzle[k][j]] = 0;
    return 0;
}

/* Finds the numbers in the same 3*3 grid and
	dismisses those numbers from respective pheromone array position for ATM*/
int setGridChoice(int i , int j) 
{
	int rowStart = (((i-1)/3)*3)+1;
	int colStart = (((j-1)/3)*3)+1;

	for(int k = 1 ; k <= 9 ; k++)
		if(puzzle[rowStart + ((k-1)%3)][colStart + ((k-1)/3)] != 0)
			ph[i][j][puzzle[rowStart + ((k-1)%3)][colStart + ((k-1)/3)]] = 0;
	return 0;
}

// Finds if there is any unsolved position left
bool isSolved()
{   
    for(int row = 1 ; row <= 9 ; row++)
        for(int col = 1 ; col <= 9 ; col++)	
			if(puzzle[row][col] == 0)
                return false;
    return true;
}


/* Searches the puzzle to find an entry that is still unassigned. If
   found, the reference parameters row, col will be set the location
   that is unassigned, and true is returned. If no unassigned entries
   remain, false is returned. */
bool FindUnassignedLocation(int &row, int &col)
{
    for (row = 1 ; row <= 9 ; row++)
        for (col = 1; col <= 9 ; col++)
            if (puzzle[row][col] == 0)
                return true;
    return false;
}

/* Returns a boolean which indicates whether an assigned entry
   in the specified row matches the given number. */
bool UsedInRow(int row, int num)
{
    for (int col = 1 ; col <= 9 ; col++)
        if (puzzle[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether an assigned entry
   in the specified column matches the given number. */
bool UsedInCol(int col, int num)
{
    for (int row = 1 ; row <= 9 ; row++)
        if (puzzle[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether an assigned entry
   within the specified 3x3 box matches the given number. */
bool UsedInGrid(int rowStart, int colStart, int num)
{
    for (int row = 1 ; row <= 3 ; row++)
        for (int col = 1 ; col <= 3 ; col++)
            if (puzzle[row+rowStart-1][col+colStart-1] == num)
                return true;
    return false;
}

/* Returns a boolean which indicates whether it will be legal to assign
   num to the given row,col location. */
bool isSafe(int row, int col, int num)
{
    /* Check if 'num' is not already placed in current row,
       current column and current 3x3 box */
    return !UsedInRow(row, num) &&
           !UsedInCol(col, num) &&
           !UsedInGrid(row - ((row-1)%3), col - ((col-1)%3), num)&&
            puzzle[row][col] == 0;
}

/* if for a row in choice array all the values are 0 except one 
	set the value in corresponding puzzle array position*/
	 
int solvePuzzleATM()
{
    int i , j , k , totalZero , setChoice , setFlag = 0;
    for(i = 1 ; i <= 9 ; i++)
	{
        for(j = 1 ; j <= 9 ; j++)
		{
            if(puzzle[i][j] == 0)
			{
            	totalZero = 0;
            	for(k = 1 ; k <= 9 ; k++)
				{
                	if(ph[i][j][k] == 0)
                    	totalZero++;
                	if(ph[i][j][k] != 0)
                    	setChoice = ph[i][j][k];  // store that one possibility
            	}
            	if(totalZero == 8) //when total no of remaining possibility is one
				{
                	puzzle[i][j] = setChoice; // setchoice is the unique value left for the unassigned box in the puzzle
                	setFlag = 1;  // setFlag stops the code from entering into infinite loop
        		}
        	}
        }
    }
    return setFlag;
}

bool solvePuzzleMA()
{
    int row, col, num , k;
    // If there is no unassigned location, we are done
    if (!FindUnassignedLocation(row, col))
       return true; // success

    for(k = 1 ; k <= 9 ; k++)
    {
        if(ph[row][col][k] != 0)
		{
            num = ph[row][col][k];
        	if (isSafe(row, col, num))
        	{
            	// make tentative assignment
            	puzzle[row][col] = num;
            	if (solvePuzzleMA())
                	return true; // success
            	puzzle[row][col] = 0; //failure , unmake amd try again
        	}
        }
    }
    return false; // fall back to previous cell
}

// For printing the solved puzzle
void printPuzzle()
{
    int row , col;
    printf("\nPuzzle Solved -\n");
    printf("----------------\n");
    printf("----------------\n");
    for(row = 1 ; row <= 9 ; row++)
	{
        printf("\n");
        for(col = 1 ; col <= 9 ; col++)
            printf("%d ",puzzle[row][col]);
    }
}

int main()
{
    int row , col , iterate;
    clock_t start , end;
	double tt;
	
	for(row = 1 ; row <= 9 ; row++)      // takes input of the sudoku from user
        for(col = 1 ; col <= 9 ; col++)
            scanf("%d",&puzzle[row][col]);
	
	start = clock();
    
	createPheromoneArray(); // Creation of choice array wrt the puzzle
	
    while(!isSolved()) // reducing possibilities and set values where find unique possibility
	{
    	for(row = 1 ; row <= 9 ; row++)
		{
        	for(col = 1 ; col <= 9 ; col++)
			{
            	if(puzzle[row][col] == 0)
				{
                	setRowChoice(row,col);
                	setColumnChoice(row,col);
                	setGridChoice(row,col);
            	}
        	}
    	}
    	iterate = solvePuzzleATM(); // Solving By ATM
    	
		if(iterate == 0) // stops the while loop from going into infinite loop when there is no improvement done
        	break;
    }
    if(!isSolved())
        solvePuzzleMA(); // Solving by making assignments for a particular blank cell
    
	printPuzzle(); // prints the solved puzzle
    
	end = clock();
	
	tt = ((double)(end-start)/CLOCKS_PER_SEC);
	printf("\n\nTT = %f",tt);
	
    return 0;
}
