#include <stdio.h>

int Answer;
#define MAX 15
struct node {
	char str[7];
};
typedef struct node Node;
Node input[MAX][MAX];

struct queue {
	int r;
	int c;
	int level;
};
typedef struct queue Q;
Q Queue[MAX*MAX];
int integer[MAX][MAX];
char string[MAX][MAX];
int visited[MAX][MAX];
int visited_temple[MAX][MAX];
int R,C;
int triger_r, triger_c;
int start_r, start_c;
int front = 0;
int rear = -1;

void print_input()
{
	int i,j;
	for(i =1; i<=R; i++)
	{
		for(j =1; j<=C; j++)
		//printf("%s ", visited[i][j]);
		printf("%d ", visited[i][j]);
		printf("\n");
	}
}
void print_int()
{
	int i,j;
	for(i =1; i<=R; i++)
	{
		for(j =1; j<=C; j++)
		printf("%d ", integer[i][j]);
		printf("\n");
	}
}
void print_string()
{
	int i,j;
	for(i =1; i<=R; i++)
	{
		for(j =1; j<=C; j++)
		printf("%c ", string[i][j]);
		printf("\n");
	}
}
void find_int_char(int r, int c, char *str)
{
	char *s =str;
	while(*str != '\0')
	{
		if(*str == 'F')
		{
			triger_r = r;
			triger_c = c;
			string[r][c] = 'F';
			str++;
		}
		else if(*str == 'P')
		{
			string[r][c] = 'P';
			str++;
			if(*str == 'E') {
			 string[r][c] = 'B';
			  str++;
			}
		}
		else if(*str == 'S')
		{
			if(s[0]== 'S')
			{
				start_r = r;
				start_c = c;
				string[r][c] = 'S';
				integer[r][c] = 0;
				str++;				
			}
			else {
			int temp;
			start_r = r;
			start_c = c;
			string[r][c] = 'S';
			*str = '\0';
			sscanf(s, "%d", &temp); 
			integer[r][c] = temp;
//			printf("temp = %d\n", temp);
			str++;
			}
		}
		else if(*str == 'E')
		{
			if(s[0]== 'E')
			{
				string[r][c] = 'E';
				integer[r][c] = 0;
				str++;				
			}
			else {
				int temp;
				string[r][c] = 'E';
				*str = '\0';
				sscanf(s, "%d", &temp); 
				integer[r][c] = temp;
				str++;	
			}
		}
		else
		{
			int temp;
			sscanf(s, "%d", &temp); 
			integer[r][c] = temp;
			str++;	
		}
	}
}
void push_element(int r, int c, int l)
{
	if(r<1 || c<1 || r>R || c>C || string[r][c] == 'P' || string[r][c] == 'B' || visited[r][c])
		return;
	visited[r][c] = l;
	rear++;
        Queue[rear].r = r;
        Queue[rear].c = c;
        Queue[rear].level = l;
	
}
Q pop_element()
{
	return Queue[front++];
	
}
void fill_lava(int r, int c, int l)
{
	push_element(r, c, l);
	while(front <= rear)
	{
		Q temp;
		int i, j,k;
		temp = pop_element();
		i  = temp.r;
		j = temp.c;
		k = temp.level;
		push_element(i+1, j, k+1);
		push_element(i-1, j, k+1);
		push_element(i, j+1, k+1);
		push_element(i, j-1, k+1);
		
	}
	
}

void temple_run(int r, int c, int level, int val)
{
	if(r<1 || c<1 || r>R || c>C || visited_temple[r][c] || level >= visited[r][c])
		return;
//	printf("int  = %d r = %d c= %d\n", integer[r][c], r, c);
	if(string[r][c] == 'E')
	{
//		printf("r = %d c = %d  val = %d\n", r, c, val);
		if(Answer < val)
			Answer = val;
	}
	visited_temple[r][c] = 1;
	temple_run(r+1, c, level+1, val+integer[r+1][c]);
	temple_run(r-1, c, level+1, val+integer[r-1][c]); 
	temple_run(r, c-1, level+1, val+integer[r][c-1]); 
	temple_run(r, c+1, level+1, val+integer[r][c+1]); 
	visited_temple[r][c] = 0;
	
}
void solve_problem()
{
	int i, j;
	scanf("%d %d", &R,&C);
	for(i =1; i<=R; i++)
	{
		for(j =1; j<=C; j++)
		{
			scanf("%s", input[i][j].str);
			integer[i][j] =0;
			string[i][j] ='A';
			visited[i][j] = 0;
			visited_temple[i][j] = 0;
			find_int_char(i, j, input[i][j].str);
			
		}
	}
	front = 0;
	rear = -1;
	Answer =0;
	fill_lava(triger_r, triger_c, 1);
//	printf("start_r = %d start_c = %d\n", start_r, start_c);
	temple_run(start_r, start_c, 1, integer[start_r][start_c]);
#if 0
	print_string();
	printf("***************************\n");
	print_int();
	printf("***************************\n");
	print_input();
	printf("***************************\n");
#endif
}

int main(void)
{
	int T, test_case;
	setbuf(stdout, NULL);

	scanf("%d", &T);
	for(test_case = 0; test_case < T; test_case++)
	{
		
		  solve_problem();
		printf("Case #%d\n", test_case+1);
		printf("%d\n", Answer);
	}

	return 0;//Your program should return 0 on normal termination.
}
