/*************************************************************************
    > File Name: helixoutput.cpp
    > Author: captain
    > Mail: ma6174@163.com 
    > Created Time: Mon 15 Feb 2016 06:51:08 PM PST
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<deque>
#include<vector>
#include<assert.h>
#include<map>
#include<algorithm>
using namespace std;

int main()
{
	int M,N;
	cout<<"M rows N columns,input M,N:"<<endl;
	cin>>M>>N;
	int **arr = (int**)malloc(M*sizeof(int *));
	for(int i = 0; i < M; i++)
	{
		arr[i] = (int*)malloc( N * sizeof(int));
	}

	int cur = 1;
	
	int a=0,b=N-1,c=0,d=M-1;

	int i = 0,j = 0;

	while(cur != M*N+1)
	{
		while(j < b )
		{
			arr[i][j++] = cur++;
		}
		c++;
		
		while(i < d )
		{
			arr[i++][j] = cur++;
		}
		b--;


		while(j > a )
		{
			arr[i][j--] = cur++;
		}
		d--;

		while(i >= c )
		{
			arr[i--][j] = cur++;
		}
		a++;
	}


	for( i = 0; i < M; i++)
	{
		for(j = 0;j < N; j++)
		{
			cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
