/*************************************************************************
    > File Name: bucket.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Sun 31 Jan 2016 10:00:13 PM PST
 ************************************************************************/

#include<iostream>
#include<cassert>
#include "bucket_state.h"
using namespace std;

int bucket_capicity[buckets_count] = {8, 5, 3};
int bucket_init_state[buckets_count]  = {8, 0, 0};
int bucket_final_state[buckets_count] = {4, 4, 0};

void CopyStateArray(const int *from, int *to, int count)
{
    for(int i = 0; i < count; ++i)
    {
        to[i] = from[i];
    }
}

BucketState::BucketState()
{
    SetBuckets(bucket_init_state);
    SetAction(8, -1, 0);
}

BucketState::BucketState(const int *buckets)
{
    SetBuckets(buckets);
    SetAction(8, -1, 0);
}

BucketState::BucketState(const BucketState& state)
{
    SetBuckets((const int *)state.bucket_s);
    SetAction(state.curAction.water, state.curAction.from, state.curAction.to);
}

BucketState& BucketState::operator=(const BucketState& state)
{
    SetBuckets((const int *)state.bucket_s);
    SetAction(state.curAction.water, state.curAction.from, state.curAction.to);
    return *this;
}

bool BucketState::IsSameState(const BucketState& state) const
{
    for(int i = 0; i < buckets_count; ++i)
    {
        if(bucket_s[i] != state.bucket_s[i])
            return false;
    }

    return true;
}

void BucketState::SetAction(int w, int f, int t)
{
    curAction.water = w;
    curAction.from  = f;
    curAction.to    = t;
}

void BucketState::SetBuckets(const int *buckets)
{
    CopyStateArray(buckets, (int *)bucket_s, buckets_count);
}

void BucketState::GetBuckets(int *buckets) const
{
    CopyStateArray((const int *)bucket_s, buckets, buckets_count);
}

bool BucketState::IsBucketEmpty(int bucket)
{
    assert((bucket >= 0) && (bucket < buckets_count));

    return (bucket_s[bucket] == 0);
}

bool BucketState::IsBucketFull(int bucket)
{
    assert((bucket >= 0) && (bucket < buckets_count));

    return (bucket_s[bucket] >= bucket_capicity[bucket]);
}

void BucketState::PrintStates()
{
    cout << "Dump " << curAction.water << " water from "
         << curAction.from + 1 << " to " << curAction.to + 1 << ", ";
    cout << "buckets water states is : ";

    for(int i = 0; i < buckets_count; ++i)
    {
        cout << bucket_s[i] << " ";
    }
    cout << endl;
}

bool BucketState::IsFinalState()
{
    return IsSameState(BucketState(bucket_final_state));
}

/*从'b4?from到'b5?to倒'b5?水'cb?，'a3?返'b7?回'bb?实'ca?际'bc?倒'b5?水'cb?体'cc?积'bb?*/
bool BucketState::DumpWater(int from, int to, BucketState& next)
{
    int bucket_water[buckets_count] = { 0 };

    GetBuckets(bucket_water);
    int dump_water = bucket_capicity[to] - bucket_water[to];
    if(bucket_water[from] >= dump_water)
    {
        bucket_water[to] += dump_water;
        bucket_water[from] -= dump_water;
    }
    else
    {
        bucket_water[to] += bucket_water[from];
        dump_water = bucket_water[from];
        bucket_water[from] = 0;
    }
    if(dump_water > 0) /*是'ca?一'd2?个'b8?有'd3?效'd0?的'b5?倒'b5?水'cb?动'b6?作'd7??*/
    {
        next.SetBuckets(bucket_water);
        next.SetAction(dump_water, from, to);
    }
    return (dump_water > 0);
}                                                                                         
