#include <iostream>
#define MAX 25

using namespace std;

int Answer;
int N;
bool Prime[500];
int MMass[MAX];
bool visit[MAX];

bool IsPrime(int n)
{
	if(n<=1)
	{
		return false;
	}
	else if(n<=3)
	{
		return true;
	}
	else if(n%2==0 || n%3==0)
	{
		return false;
	}
	int i = 5;
	while(i*i <= n)
	{
		if(n%i == 0 || n%(i+2) == 0)
		{
			return false;
		}
		i = i+6;
	}

	return true;
}

void FindMaxMass(int mass, int AAChain)
{
	//save ans
	{
		if(Answer<mass)
			Answer = mass;
	}

	for(int i = 1; i<=N; i++)
	{
		if(!visit[i] && Prime[AAChain+i])
		{
			visit[i] = true;
			FindMaxMass(mass+MMass[i], AAChain+i);
			visit[i] = false;
		}
	}
}

int main(int argc, char** argv)
{
	int T, test_case;

	for(int i = 1; i<=500; i++)
	{
		Prime[i] = IsPrime(i);
	}

	//freopen("HeaviestProtien.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		Answer = 0;

		cin >> N;

		for(int i=1; i<=N; i++)
		{
			cin >> MMass[i];
			visit[i] = false;
		}

		for(int i = 1; i<=N; i++)
		{
			if(Prime[i])
			{
				visit[i] = true;
				FindMaxMass(MMass[i], i);
				visit[i] = false;
			}
		}
		
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;
}

