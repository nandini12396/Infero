#include <stdio.h>
int N, M;
int pL, pR, cL, cR;
int matrix[11][11][2];
int moves=999999;

int solve(int pL, int cL, int pR, int cR, int dir, int count)
{
	int i, j;

	if ((pL>0 && pL < cL) || (pR<cR && pR>0))
		return;

	if (matrix[pL][cL][dir]>0 && matrix[pL][cL][dir] <= count)
		return;

	if (pL == 0 && cL == 0)
	{
		if (moves > count)
			moves = count;
		return;
	}

	matrix[pL][cL][dir] = count;
	if (dir == 0)  /*left to right */
	{
		for (i = pL; i >=0; i--)
		{
			for (j = cL; j >=0; j--)
			{
				if (((i + j) > M) || ((i + j) == 0) || (i>0&&j > i)) continue;
				solve(pL - i, cL - j, pR + i, cR + j, 1, count + 1);
			}
		}
	}
	else /*right to left */
	{
		for (i = pR; i >=0; i--)
		{
			for (j = cR; j >= 0; j--)
			{
				if (((i + j )> M) || ((i + j) == 0) || (i>0&&j > i)) continue;
				solve(pL + i, cL + j, pR - i, cR - j, 0, count + 1);
			}
		}

	}
}

int main(void)
{
	int tc, T;

	// The freopen function below opens input.txt file in read only mode, and afterward,
	// the program will read from input.txt file instead of standard(keyboard) input.
	// To test your program, you may save input data in input.txt file,
	// and use freopen function to read from the file when using scanf function.
	// You may remove the comment symbols(//) in the below statement and use it.
	// But before submission, you must remove the freopen function or rewrite comment symbols(//).

	//freopen("cannibles_input.txt", "r", stdin);

	// If you remove the statement below, your program's output may not be rocorded
	// when your program is terminated after the time limit.
	// For safety, please use setbuf(stdout, NULL); statement.

	setbuf(stdout, NULL);

	scanf("%d", &T);
	for (tc = 0; tc < T; tc++)
	{
		int i, j;

		scanf("%d %d", &N, &M);

		for (i = 0; i < 11;i++)
		for (j = 0; j < 11; j++)
		{
			matrix[i][j][0] = 0;
			matrix[i][j][1] = 0;
		}

		pL = cL = N;
		pR = cR = 0;
		moves = 99999;
		solve(pL,cL, pR, cR, 0, 0);

		/**********************************
		*  Implement your algorithm here. *
		***********************************/

		// Print the answer to standard output(screen).
        if(moves==99999)
            printf("impossible\n");
        else
		printf("%d\n", moves);
	}

	return 0;//Your program should return 0 on normal termination.
}

