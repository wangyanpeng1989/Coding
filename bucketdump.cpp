#include<iostream>
#include<string.h>
#include<deque>
#include<algorithm>
#include<assert.h>
using namespace std;

const int BUCKET_COUNT = 3;

int bucket_capicity[3] = {3,5,8};
int bucket_init[3] = {0,0,8};
int bucket_final[3] = {0,4,4};

typedef struct tagAction
{
	int from;
	int to;
	int water;
}ACTION;

struct BucketState{
	int bucket_s[BUCKET_COUNT];
	ACTION curAction;
	BucketState();
	bool CanTakeDumpAction(int from, int to);
	bool DumpWater(int from, int to, BucketState & next);
	bool IsBucketEmpty(int from);
	bool IsBucketFull(int to);
	bool IsFinalState();
	void SetBucket(int *bucket_water);
	void GetBucket( int* bucket_cur );
	void SetAction(int from, int to, int water);
	bool IsSameState(BucketState newstate);
};

void PrintResult(deque<BucketState> &state);
void SearchStateOnAction(deque<BucketState>& state, BucketState current, int i, int j);

BucketState::BucketState()
{	
	SetAction(-1,2,8);
	SetBucket(bucket_init);
}

void BucketState::SetBucket(int *bucket_water)
{
	memcpy((int*)bucket_s,bucket_water,sizeof(bucket_water));
	/*
	for(int i =0;i<BUCKET_COUNT;i++)
	{
		bucket_s[i] = bucket_water[i];
	}
	*/
}

void BucketState::GetBucket(int* bucket_water)
{
	memcpy(bucket_water,(int*)bucket_s,sizeof(bucket_s));
	/*
	for(int i =0;i<BUCKET_COUNT;i++)
	{
		bucket_water[i] = bucket_s[i];
	}
	*/
}

bool BucketState::IsSameState(BucketState newstate)
{
	return bucket_s[0] == newstate.bucket_s[0] && bucket_s[1] == newstate.bucket_s[1] && bucket_s[2] == newstate.bucket_s[2];
}

void BucketState::SetAction(int from, int to, int water)
{
	curAction.from = from;
	curAction.to = to;
	curAction.water = water;
}

bool BucketState::IsBucketEmpty(int from)
{
	return bucket_s[from] == 0;
}

bool BucketState::IsBucketFull(int to)
{
	if( to == 0)
	{
		return bucket_s[to] >= 3;
	}
	else if( to == 1)
	{
		return bucket_s[to] >= 5;
	}
	else if( to == 2)
	{
		return bucket_s[to] >= 8;
	}
	return false;
}

bool BucketState::IsFinalState()
{
	if(bucket_s[0] == 0 && bucket_s[1] == 4 && bucket_s[2] == 4)
	{
		return true;
	}
	return false;
}

bool BucketState::CanTakeDumpAction(int from,int to)
{
	assert(from >= 0 && from < BUCKET_COUNT);
	assert(to >= 0 && to < BUCKET_COUNT);

	if((from != to) && !IsBucketEmpty(from) && !IsBucketFull(to))
	{
		return true;
	}
	return false;
}

bool BucketState::DumpWater(int from, int to, BucketState & next)
{
	int bucket_cur[BUCKET_COUNT] = {0};
	 
	GetBucket( bucket_cur );

	int dump_water = bucket_capicity[to] - bucket_cur[to];//能倒进水的最大数
	//cout<<"TryDumpWater:from "<<from<<" "<<bucket_cur[from]<<" to "<<to<<" "<<bucket_cur[to]<<" "<<dump_water<<endl;
	if(bucket_cur[from] >= dump_water)
	{
		bucket_cur[to] += dump_water;
		bucket_cur[from] -= dump_water;
	}
	else//能全部倒进去
	{
		bucket_cur[to] += bucket_cur[from];
		dump_water = bucket_cur[from];
		bucket_cur[from] = 0;
	}
	if(dump_water > 0) //是一个有效的倒水动作
	{
		next.SetAction(from, to, dump_water);//当前状态是从什么状态变成的
		next.SetBucket(bucket_cur);
		//cout<<"from:"<<from<<" to:"<<to<<" dump_water:"<<dump_water<<endl;
	}
	return dump_water>0;
}

bool IsSameState(BucketState oldstate, BucketState newstate)
{
	return oldstate.IsSameState(newstate);
}

bool IsProcessedState(deque<BucketState>& state, BucketState newstate)
{
	deque<BucketState>::iterator it = state.begin();
	it = find_if(state.begin(),state.end(),bind2nd(ptr_fun(IsSameState),newstate));
	return it != state.end();//如果找到相同的
}

void SearchState(deque<BucketState> &state)
{
	BucketState current = state.back();
	if(current.IsFinalState())
	{
		PrintResult(state);
		return;
	}
	for(int i=0; i< BUCKET_COUNT; i++)
	{
		for(int j=0; j< BUCKET_COUNT; j++)
		{
			SearchStateOnAction(state, current, i, j);
		}
	}
}

void SearchStateOnAction(deque<BucketState>& state, BucketState current, int from, int to)
{
	if(current.CanTakeDumpAction(from,to))
	{
		BucketState next;
		bool bDump = current.DumpWater(from, to, next);

		if(bDump && !IsProcessedState(state, next))
		{
			state.push_back(next);
			SearchState(state);
			state.pop_back();
		}
	}
}

void PrintResult(deque<BucketState> &state)
{
	deque<BucketState>::iterator it = state.begin();
	cout<<"Result:"<<endl;
	while( it != state.end()){
		cout<<it->bucket_s[0]<<" "<<it->bucket_s[1]<<" "<<it->bucket_s[2]<<endl;
		it++;
	}
	cout<<endl;
}

int main()
{
	BucketState bs;
	deque<BucketState> dq;
	dq.push_back(bs);
	SearchState(dq);
	return 0;
}
