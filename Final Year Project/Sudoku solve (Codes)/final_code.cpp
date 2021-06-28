#include<stdio.h>
#include<stdlib.h>

int puzzle[9][9];
int ch[9][9][9];



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

int solvePuzzle(){


    int i,j,k,totalZero,setChoice;
    for(i=1;i<10;i++){
        for(j=1;j<10;j++){
            totalZero=0;
            for(k=1;k<10;k++){
                //printf("\n%d",ch[i][j][k]);
                if(ch[i][j][k]==0)
                    totalZero++;
                if(ch[i][j][k]!=0)
                    setChoice=ch[i][j][k];
            }
            if(totalZero==8)
                puzzle[i][j]=setChoice;
        }
    }
    return 0;
}

int isSolve(){
    int i,j;
    for(i=1;i<10;i++){
        for(j=1;j<10;j++){
            if(puzzle[i][j]==0)
                return 1;
        }
    }
    return 0;
}

int printPuzzle(){
    int i,j;
    for(i=1;i<10;i++){
        printf("\n");
        for(j=1;j<10;j++){
            printf("%d ",puzzle[i][j]);
        }
    }
}

int main()
{
    int i,j,k;

	for(i = 1 ; i <= 9 ; i++)
        for(j = 1 ; j <= 9 ; j++)
            scanf("%d",&puzzle[i][j]);

    for(i = 1 ; i <= 9 ; i++)
	{
        for(j = 1 ; j <= 9 ; j++)
		{
        	for(k = 1 ; k <= 9 ; k++)
                ch[i][j][k]=k;
        }
    }

    while(isSolve()){
    for(i=1;i<10;i++){
        for(j=1;j<10;j++){
            if(puzzle[i][j]==0){
                setRowChoice(i,j);
                setColumnChoice(i,j);
                setGridChoice(i,j);

            }
        }
    }
    solvePuzzle();
    }
    printf("Puzzle Solved-----\n");
    printPuzzle();


    return 0;
}
