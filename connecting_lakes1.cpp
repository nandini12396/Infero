#include<iostream>
#include <stdio.h>

using namespace std;
struct node
{
	int row, col;
	struct node *next;
};
class queue
{
	node *head, *tail;
	public:
		queue()
		{
			head = NULL;
			tail = NULL;
		}
		void enqueue(int a, int b)
		{
			node *temp = new node;
			temp->row = a;
			temp->col = b;
			temp->next = NULL;
			if(head == NULL)
				head = temp;
			else
				tail->next = temp;
			tail = temp;
		}
		void dequeue(int &a, int  &b)
		{
			a = head->row;
			b = head->col;
			head = head->next;
		}
		int empty()
		{
			if(head == NULL)
				return true;
			else
				return false;
		}
};
int max(int a, int b)
{
	if(a > b)
		return a;
	else
		return b;
}
int min(int a, int b)
{
	if(a < b)
		return a;
	else
		return b;
}
int main()
{
	int test_cases, n, m;
	char **input;
	int **grid;
	int i,j,k;
	
	cin >> test_cases;
	for(i=1;i<=test_cases;i++)
	{
		cin >> n;
		cin >> m;
		
		if(m < 0 && n < 0)
			continue;
			
		input = (char **) new char*[n];
		for(j=0;j<n;j++)
			input[j] = (char*)new char[m];

		grid = (int **) new int*[n];
		for(j=0;j<n;j++)
			grid[j] = (int*)new int[m];
		
		queue q;
		q.enqueue(0,0);
		
		for(j=0;j<n;j++)
		{
			for(k=0;k<m;k++)
			{
				cin >> input[j][k];
	//			cout << input[j][k] << " ";
			}	
	//		cout << "\n";
		}
		
		cout << "Case #" << i << endl;
				
		int row = 0, col = 0;
		//connected and shortest path -----
		
		while(!q.empty())
		{
			q.dequeue(row, col);

			if(row == n-1 && col == m-1)
			{
			}
			else if(row == n-1)
				q.enqueue(row, col+1);
			else if(col == m-1)
				q.enqueue(row+1, col);
			else if(row != n-1 && col != m-1)
			{
				q.enqueue(row+1, col);
				q.enqueue(row, col+1);
			}
		
			if(row == 0 && col == 0)
			{
				grid[row][col] = 0;
			}
			if(row == 0 && col != 0)
			{
				if(input[row][col] == '1' || input[row][col] == '2' || input[row][col] == '3')
				{
					int temp = grid[row][col - 1];
					if(temp == -1)
						grid[row][col] = -1;
					else
						grid[row][col] = temp;
				}
				if(input[row][col] == '#')
					grid[row][col] = -1;
				if(input[row][col] == '.')
					grid[row][col] = grid[row][col-1] + 1;
			}
			if(row != 0 && col == 0)
			{
				if(input[row][col] == '1' || input[row][col] == '2' || input[row][col] == '3')
				{
					int temp = grid[row-1][col];
					if(temp == -1)
						grid[row][col] = -1;
					else
						grid[row][col] = temp;
				}
				if(input[row][col] == '#')
					grid[row][col] = -1;
				if(input[row][col] == '.')
					grid[row][col] = grid[row-1][col] + 1;
			}
			if(row != 0 && col != 0)
			{
				if(input[row][col] == '1' || input[row][col] == '2' || input[row][col] == '3')
				{
					int temp = min(grid[row-1][col], grid[row][col-1]);
					if(temp == -1)
					{
						temp = max(grid[row-1][col], grid[row][col-1]);
						if(temp == -1)
							grid[row][col] = -1;
					}
					grid[row][col] = temp;
				}
				if(input[row][col] == '#')
					grid[row][col] = -1;
				if(input[row][col] == '.')
				{
					int temp = min(grid[row-1][col], grid[row][col-1]);
					if(temp == -1)
					{
						temp = max(grid[row-1][col], grid[row][col-1]);
						if(temp == -1)
							grid[row][col] = -1;
					}
					grid[row][col] = temp + 1;
				}
			}
 		}
		int temp;
		for(j=0;j<n;j++)
		{
			for(k=0;k<m;k++)
			{
				if(input[j][k] == '1' || input[j][k] == '2' || input[j][k] == '3')		
					if(grid[j][k] == -1)
					{
						cout << "-1" << endl;
						goto l1;
					}
			}
		}
		
		temp = -1;
		for(j=n-1;j>=0;j--)
		{
			for(k=m-1;k>=0;k--)
			{
				if(input[j][k] == '1' || input[j][k] == '2' || input[j][k] == '3')	
					temp = max(temp, grid[j][k]);
			}
		}
		cout << temp << endl;
l1:	;
	}
	return 0;
}

