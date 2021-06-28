// test run for 9*9*9 multidimensional array

#include<stdio.h>
#include<stdlib.h>

int puzzle[9][9]; // Sudoku
int ch[9][9][9];

int setRowChoice(int i , int j)
{	
    int k;
    for(k=1 ; k <= 9 ; k++)
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


/*int zeroCount(int i , int j)
{
	int k , count;
	count = 0;
	for(k = 1 ; k <= 9 ; k++)
	{
		if(ch[i][j][k] != 0)
			count++;
		if(count > 1)
		{
			return 0;
		}
	}
	return k;
}


void putValue()
{
	int i , j , k;
	for(i = 1 ; i <= 9 ; i++)
	{
		for(j = 1 ; j <= 9 ; j++)
		{
			if(zeroCount(i,j) > 0)
				puzzle[i][j] = ch[i][j][k];
		}
	}
}*/

void printPuzzle()
{
	int i , j;
	for(i = 1 ; i <= 9 ; i++)
	{
		for(j = 1 ; j <= 9 ; j++)
		{
			printf("%d ",puzzle[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int i , j , k;
	
	for(i = 1 ; i <= 9 ; i++)
		for(j = 1 ; j <= 9 ; j++)
			scanf("%d",&puzzle[i][j]);
			
	
			
	for(i = 1 ; i <= 9 ; i++)
	{
		for(j = 1 ; j <= 9 ; j++)
		{
			for(k = 1 ; k <= 9 ; k++)
			{
				ch[i][j][k] = k;
			}
		}
	}
	
	
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
	
	printf("************************\n");
	printf("************************\n\n");
	
	for(i = 1 ; i <= 9 ; i++)
	{
		for(j = 1 ; j <= 9 ; j++)
		{
			for(k = 1 ; k <= 9 ; k++)
			{
				printf("%d ",ch[i][j][k]);
			}
			printf("\n");
		}
		printf("-----------------------\n");
		printf("-----------------------\n\n");
	}
	
	//putValue();
	//printPuzzle();
	
	return 0;
}



