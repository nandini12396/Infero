#include <iostream>
#include<queue>

using namespace std;

int Answer;
bool prime[10000];
int data[10000];
bool vis[10000];

void init()
{
	for(int i=0;i<10000;i++)
		data[i]=0,vis[i]=false;
}

//prime number generator
void func()
{
	for(int i=2;i<=100;i++)
{
        if(!prime[i])
        {
            for(int j=i*i;j<=10000;j+=i)
                prime[j] = true;
        }
    }
}

int solve(int a,int b)
{
	int count=0;
	//int queue
	queue<int>  q;
	q.push(a);
	data[a]=0;
	vis[a]=true;


	while(!q.empty())
	{
	  int temp=q.front();
	  q.pop();
	  vis[temp]=true;
	  
	  if(b==temp)
		  break;
	  for(int i=3;i>=0;i--)
	  {
		  int x;
		  int temp1=0,temp2=0;
		  if(i==3)
		  {
			   temp1=temp/10;
			   temp2=temp%10;
		  }
		  if(i==2)
		  {
			  temp1=temp/100;
			   temp2=temp%10;

		  }
		  if(i==1)
		  {
			  temp1=temp/1000;
			  temp2=temp%100;
		  }
		  if(i==0)
		  {
			  temp1=0;
			  temp2=temp%1000;
		  }

		  for(int j=0;j<=9;j++)
		  {
			  int temp3=0;
			  if(i==0)
			  {
				  temp3=(j*1000)+temp2;
			  }
			  else if(i==1)
			  {
				  temp3=(temp1*1000)+(j*100)+temp2;
			  }
			  else  if(i==2)
			  {
				  temp3=(temp1*100)+(j*10)+temp2;
			  }
			  else
			  {
				  temp3=(temp1*10)+j;
			  }

			  if(temp3>1000 && !prime[temp3] )
			  {
				  if(!vis[temp3]){
				  data[temp3]=data[temp]+1;
				//  else if(data[temp3] < (data[temp]+1))
				//	  data[temp3]=data[temp]+1;

				  q.push(temp3);
			     vis[temp3]=true;
				  }
			  }			  
		  }
	  }

	}

	return 0;
}
int main(int argc, char** argv)
{
	int T, test_case;
	func();
	
	cin >> T;
	//cout<<prime[1033 ]<<prime[8179]<<prime[2]<<prime[4]<<endl;
	for(test_case = 0; test_case  < T; test_case++)
	{
	      init();
		Answer = 0;
		int num1,num2;
		cin>>num1>>num2;
		if(num1==num2)
			;
		else
			solve(num1,num2);

		Answer=data[num2];
		
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;
}
