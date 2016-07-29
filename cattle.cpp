#include <iostream>

using namespace std;
struct Point
{
	int x,y;
	int position;
	Point(int x1, int y1, int pos)
	{
		x = x1;
		y = y1;
		position = pos;
	}
	Point()
	{
		x = 0;
		y = 0;
		position = 0;
	}
};

int noOfCattle;
Point CattlePosition[50];
Point ptStack[50];

void SwapPoint(int i, int j)
{
	int tempx, tempy, tempPos;
	tempx = CattlePosition[i].x; tempy = CattlePosition[i].y, tempPos = CattlePosition[i].position;
	CattlePosition[i].x = CattlePosition[j].x; CattlePosition[i].y = CattlePosition[j].y; CattlePosition[i].position = CattlePosition[j].position;
	CattlePosition[j].x = tempx; CattlePosition[j].y = tempy; CattlePosition[j].position = tempPos;
}

int Direction(Point p, Point q, Point r)
{

	int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise

	//Point P2Dash(P2.x-P1.x,P2.y-P1.y,0);
	//Point P3Dash(P3.x-P1.x,P3.y-P1.y,0);
	//int val = (P2Dash.x*P3Dash.y) - (P3Dash.x*P2Dash.y);
	//if(val == 0) 
	//	return 0;
	//else
	//	return val>0? 1: 2; //1 clockwise, 2 counterclockwise
}

int Orinetation(Point P1, Point P2, Point P3)
{
	Point P2Dash(P2.x-P1.x,P2.y-P1.y,0);
	Point P3Dash(P3.x-P1.x,P3.y-P1.y,0);
	int val = (P2Dash.x*P3Dash.y) - (P3Dash.x*P2Dash.y);

	if(val == 0)
	{
		if((P3.x*P3.x+P3.y+P3.y)>(P2.x*P2.x+P2.y+P2.y))
			return 1;
		else
			return 2;
	}
	else
		return val>0? 1: 2; //1 clockwise, 2 counterclockwise
}

int ConvexHull()
{
	//Sort remaining points
	for(int i=1 ;i< noOfCattle; i++)
	{
		for(int j=i+1 ;j< noOfCattle; j++)
		{
			if(Orinetation(CattlePosition[0], CattlePosition[i], CattlePosition[j]) == 2)
			{
				SwapPoint(i, j);
			}
		}
	}

	//remove inward points
	int m=1;
	for(int i=1; i<noOfCattle; i++)
	{
		while(i<noOfCattle-1 && Direction(CattlePosition[0], CattlePosition[i], CattlePosition[i+1]) ==0)
			i++;

		CattlePosition[m] = CattlePosition[i];
        m++;
	}
	if(m<3)
		return 0;

	ptStack[0] = CattlePosition[0];
	ptStack[1] = CattlePosition[1];
	ptStack[2] = CattlePosition[2];
	int stackTop = 2;
	for(int i=3; i<m; i++)
	{
		while(i<noOfCattle)
		{
			int val = Direction(ptStack[stackTop-1], ptStack[stackTop], CattlePosition[i]);
			if(val!=2)
			{
				stackTop--;
			}
			else
				break;
		}

		if(i<noOfCattle)
		{
		stackTop++;
		ptStack[stackTop] = CattlePosition[i];
		}
	}
	return stackTop+1;
}

int main(int argc, char** argv)
{
	int T, test_case;


	//freopen("CattleFencing.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		cin>>noOfCattle;
		cin>>CattlePosition[0].x>>CattlePosition[0].y;
		CattlePosition[0].position = 1;
		int yMin = CattlePosition[0].y, min = 0;
		for(int i=1; i<noOfCattle; i++)
		{
			cin>>CattlePosition[i].x>>CattlePosition[i].y;
			CattlePosition[i].position = i+1;
			if(CattlePosition[i].y<yMin || (yMin==CattlePosition[i].y && CattlePosition[i].x<CattlePosition[min].x))
			{
				yMin = CattlePosition[i].y;
				min = i;
			}
		}
		//place bottommost point at 0 position
		SwapPoint(0,min);
				
		int count = ConvexHull();

		cout << "Case #" << test_case+1 << endl;
		for(int i =0; i<count; i++)
		{
			cout << ptStack[i].position << " ";
		}
		cout<<endl;
	}

	return 0;
}

