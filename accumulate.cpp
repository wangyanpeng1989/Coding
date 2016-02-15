/*************************************************************************
    > File Name: accumulate.cpp
    > Author: captain
    > Mail: ma6174@163.com 
    > Created Time: Sun 14 Feb 2016 09:40:11 PM PST
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<deque>
#include<vector>
#include<assert.h>
#include<map>
//#include<functional>
#include<algorithm>
//#include<numeric>
using namespace std;


int main()
{
	int arr[]={16,2,16,4,5};
	//int answer = accumulate(arr,arr+3,0);
	//cout<<answer;
	/*do{
		cout<<arr[0]<<" "<<arr[1]<<" "<<arr[2]<<endl;
	}while(next_permutation(arr,arr+3));
	*/
	cout<<count_if(arr,arr+5,greater16);
	//cout<<arr[0]<<" "<<arr[1]<<" "<<arr[2]<<endl;

}
