#include <stdio.h>

static int grid[9][9];

void read_grid(FILE *fp)
{
	int i,j;
	for (i=0; i < 9; ++i)
	{
		char buf[16];
		fgets(buf, sizeof buf, fp);
		for (j=0; j < 9; ++j)
		{
			char c = buf[j];
				if ('1' <= c && c <= '9') grid[i][j] = c - '0';
		}
	}
}

void write_grid(void)
{
	int i, j;
	for (i=0; i < 9; ++i)
	{
		for (j=0; j < 9; ++j) printf("%d ", grid[i][j]);
		putchar('\n');
	}
}

int is_legal(int row, int col, int val)
{
	int ii = row - row%3;
	int jj = col - col%3;
	int i, j, k = 0, res = 1;
	for (i=0; i < 3; ++i)
		for (j=0; j < 3; ++j, ++k)
			res = res && (grid[row][k] != val) && (grid[k][col] != val) &&
			(grid[ii+i][jj+j] != val);
	return res;
}

void solve(int pos)
{
	if (pos == 9*9) write_grid();
	else
	{
		int row, col, val;
		row = pos / 9;
		col = pos % 9;
		if (grid[row][col] != 0) solve(pos+1);
		else
		{
			for (val=1; val <= 9; ++val)
			{
				if (is_legal(row, col, val))
				{
					grid[row][col] = val;
					solve(pos+1);
				}
			}
			grid[row][col] = 0;
		}
	}
}

int main(void)
{
	read_grid(stdin);
	solve(0);
	return 0;
}
