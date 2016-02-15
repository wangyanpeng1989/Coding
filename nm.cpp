/*************************************************************************
    > File Name: nm.cpp
    > Author: captain
    > Mail: ma6174@163.com 
    > Created Time: Sun 14 Feb 2016 10:44:36 PM PST
	> Description:输入两个整数 n 和 m，从数列1，2，3.......n 中 随意取几个数, 使其和等于 m
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<deque>
#include<vector>
#include<assert.h>
#include<map>
#include<algorithm>
#include<stdio.h>
using namespace std;

typedef struct tagObject
{
	int value;
	bool used;
}object;

int N,M;
vector<int> result(0);

void printresult( vector<int>result )
{
	vector<int>::iterator it = result.begin();
	for(; it != result.end(); it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

void search( int begin,vector<int>result, int current)
{
	//printf("current = %d\n",current);
	if(current==M)
	{
		printresult(result);
		return;
	}
	if(begin > N || current > M)
	{
		return;
	}
	//for(int i = begin;i<=N;i++)
	{
		if( current+begin <= M)
		{
			//分两种情况,放入
			result.push_back(begin);
			current += begin; 
			search(begin+1, result, current);
			
			//不放入
			current -= begin;
			result.pop_back();
			search(begin+1, result, current);
		}
	}
}

int main()
{
	N = 10, M = 20;
	search(1,result,0);
	return 0;
}
