#include <iostream>

using namespace std;

int Answer;
int N;
int chess[4][4];
int visited[4][4];



int check(int i, int j)
{
	int can = 0;
	int itemp = i;
	int jtemp = j;
	while ((i - 1) >= 0)
	{
		if (chess[i-1][j] == 99)
		{
			break;
		}
		if (visited[i-1][j] == 1)
		{
			can = 1;
			return 1;
		}
		i--;
	}
	i = itemp;
	while ((i + 1) < N)
	{
		if (chess[i+1][j] == 99)
		{
			break;
		}
		if (visited[i+1][j] == 1)
		{
			can = 1;
			return 1;
		}
		i++;
	}
	i = itemp;
	while ((j - 1) >= 0)
	{
		if (chess[i][j-1] == 99)
		{
			break;
		}
		if (visited[i][j-1] == 1)
		{
			can = 1;
			return 1;
		}
		j--;
	}
	j = jtemp;
	while ((j + 1) < N)
	{
		if (chess[i][j+1] == 99)
		{
			break;
		}
		if (visited[i][j+1] == 1)
		{
			can = 1;
			return 1;
		}
		j++;
	}
	return 0;
}

void steps(int m, int n, int cal)
{
	visited[m][n] = 1;
	if (cal > Answer)
	{
		Answer = cal;
	}
	int j=n;
	for (int i = m; i < N; i++)
	{
		for (; j < N; j++)
		{
			if ((visited[i][j] == 0)
				&&
				(chess[i][j] != 99))
			{
				if (check(i, j) == 0)
				{
					steps(i, j, cal+1);
				}
			}
		}
		j = 0;
	}
	visited[m][n] = 0;
}


int main(int argc, char** argv)
{
	int T, test_case;
	char c;
	// freopen("input.txt", "r", stdin);

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				visited[i][j] = 0;
				cin >> c;
				if (c == '.')
				{
					chess[i][j] = 0;
				}
				else
				{
					chess[i][j] = 99;
				}
			}
		}
		Answer = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (chess[i][j] == 0)
				{
					steps(i, j, 1);
				}
			}
		}

		// Print the answer to standard output(screen).
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}

