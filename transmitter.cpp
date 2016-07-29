#include <iostream>

using namespace std;

#define MAX_SIZE 15
#define INF 99999

int NUM[MAX_SIZE];

int minCost, N;

void permute(int num, int cost)
{
	if(num == 0)
	{
		if(cost < minCost) minCost = cost;
		return;
	}
	if(cost > minCost)
		return;

	for(int i = 0; i < 2*N-num-1; i++)
	{
		if(NUM[i] == -1 && NUM[i+num+1] == -1)
		{
			NUM[i] = num; NUM[i+num+1] = num;
			
			int c = cost + num * 100 *( i +  i + num + 1);
			permute(num-1, c);
			
			NUM[i] = -1; NUM[i+num+1] = -1;
		}
	}
}

int main(int argc, char** argv)
{
	int T, test_case;

#ifdef TEST
	freopen("Input_SoTong_TransmitterPlacementProblem.txt", "r", stdin);
#endif

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		minCost = INF;
		cin >> N;

		for(int i = 0; i < 2*N; i++)
		{
			NUM[i] = -1;
		}

		permute(N, 0);
		if(minCost == INF) minCost = -1;

		cout << "Case #" << test_case+1 << endl;
		cout << minCost << endl;
	}

	return 0;
}
