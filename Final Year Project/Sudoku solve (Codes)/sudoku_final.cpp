#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int puzzle[9][9];
int ch[9][9][9];

void createChoiceArray()
{
	int i , j , k;
	for(i = 1 ; i <= 9 ; i++)
	{
        for(j = 1 ; j <= 9 ; j++)
		{
        	for(k = 1 ; k <= 9 ; k++)
                ch[i][j][k] = k;
        }
    }
}

int setRowChoice(int i , int j)
{
    int k;

	for(k = 1 ; k <= 9 ; k++)
	{
        if(puzzle[i][k] != 0)
		{
            ch[i][j][puzzle[i][k]] = 0;
        }
    }
    return 0;
}

int setColumnChoice(int i , int j)
{
    int k;

    for(k = 1 ; k <= 9 ; k++)
	{
        if(puzzle[k][j] != 0)
		{
            ch[i][j][puzzle[k][j]] = 0;
        }
    }
    return 0;
}


int setGridChoice(int i , int j)
{
	int k;
	int rowStart = (((i-1)/3)*3)+1;
	int colStart = (((j-1)/3)*3)+1;

	for(k = 1 ; k <= 9 ; k++)
	{
		if(puzzle[rowStart + ((k-1)%3)][colStart + ((k-1)/3)] != 0)
		{
			ch[i][j][puzzle[rowStart + ((k-1)%3)][colStart + ((k-1)/3)]] = 0;
		}
	}
	return 0;
}


int solvePuzzle()
{
    int i , j , k , totalZero , setChoice , setFlag = 0;
    
	for(i = 1 ; i <= 9 ; i++)
	{
        for(j = 1 ; j <= 9 ; j++)
		{
            totalZero = 0;
            for(k = 1 ; k <= 9 ; k++)
			{
                if(ch[i][j][k] == 0)
                    totalZero++;
                if(ch[i][j][k] != 0)
                    setChoice = ch[i][j][k];
            }
            if(totalZero == 8)
            {
                puzzle[i][j] = setChoice;
            	setFlag = 1;    
        	}
        }
    }
    return setFlag;
}

int isSolve()
{
    int i , j;
    for(i = 1 ; i <= 9 ; i++)
	{
        for(j = 1 ; j <= 9 ; j++)
		{
            if(puzzle[i][j] == 0)
				return 1;
        }
    }
    return 0;
}

int printPuzzle()
{
    int i , j;
    
    printf("\n\nPuzzle Solved\n\n");
    printf("---------------------\n");
    printf("---------------------");
    
	for(i = 1 ; i  <= 9 ; i++)
	{
        printf("\n");
        for(j = 1 ; j <= 9 ; j++)
		{
            printf("%d ",puzzle[i][j]);
        }
    }
}

//Backtrack Algorithm

/* Searches the grid to find an entry that is still unassigned. If
   found, the reference parameters row, col will be set the location
   that is unassigned, and true is returned. If no unassigned entries
   remain, false is returned. */
bool FindUnassignedLocation(int puzzle[9][9], int &row, int &col)
{
    for (row = 1; row < 10; row++)
        for (col = 1; col < 10; col++)
            if (puzzle[row][col] == 0)
                return true;
    return false;
}

/* Returns a boolean which indicates whether an assigned entry
   in the specified row matches the given number. */
bool UsedInRow(int puzzle[9][9], int row, int num)
{
    for (int col = 1; col < 10; col++)
        if (puzzle[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether an assigned entry
   in the specified column matches the given number. */
bool UsedInCol(int puzzle[9][9], int col, int num)
{
    for (int row = 1; row < 10; row++)
        if (puzzle[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether an assigned entry
   within the specified 3x3 box matches the given number. */
bool UsedInBox(int puzzle[9][9], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 1; row < 4; row++)
        for (int col = 1; col < 4; col++)
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
    int row, col,num;
    // If there is no unassigned location, we are done
    if (!FindUnassignedLocation(puzzle, row, col))
       return true; // success!

    // consider digits 1 to 9
    for(int k=1;k<10;k++)
    {
        if(ch[row][col][k]!=0){
            num=ch[row][col][k];
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

int main()
{
    int i , j , iterate;
	clock_t start , end;
	double tt;
	
	for(i = 1 ; i <= 9 ; i++)
        for(j = 1 ; j <= 9 ; j++)
            scanf("%d",&puzzle[i][j]);
    
	start = clock();
	createChoiceArray();
	
	do
	{
    	for(i = 1 ; i <= 9 ; i++)
		{
        	for(j = 1 ; j <= 9 ; j++)
			{
            	if(puzzle[i][j] == 0)
				{
                	setRowChoice(i,j);
                	setColumnChoice(i,j);
                	setGridChoice(i,j);
				}
        	}
    	}
    	iterate = solvePuzzle();
    	
		if(iterate == 0)
    		break;
    }
    while(isSolve());
    
    if(isSolve())
    	SolveSudoku(puzzle);
    
    end = clock();
    printPuzzle();
    
	tt = ((double)(end-start)/CLOCKS_PER_SEC);
    printf("\n%f",tt);
	
	return 0;
}

