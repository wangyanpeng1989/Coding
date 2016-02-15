#include <stdio.h>
#include <deque>
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <cassert>
#include "bucket_state.h"

using namespace std;


bool IsSameBucketState(BucketState state1, BucketState state2)
{
    return state1.IsSameState(state2);
}

bool IsProcessedState(deque<BucketState>& states, const BucketState& newState)
{
    deque<BucketState>::iterator it = states.end();

    it = find_if( states.begin(), states.end(),
                  bind2nd(ptr_fun(IsSameBucketState), newState) );

    return (it != states.end());
}

void PrintResult(deque<BucketState>& states)
{
    cout << "Find Result : " << endl;
    for_each(states.begin(), states.end(),
             mem_fun_ref(&BucketState::PrintStates));
    cout << endl << endl;
}

bool IsCurrentActionValid(BucketState& current, int from, int to)
{
    /*不'b2?是'ca?同'cd?一'd2?个'b8?桶'cd?，'a3?且'c7?from桶'cd?中'd6?有'd3?水'cb?，'a3?且'c7?to桶'cd?中'd6?不'b2?满'c2?*/
    if( (from != to)
        && !current.IsBucketEmpty(from)
        && !current.IsBucketFull(to) )
    {
        return true;
    }

    return false;
}

void SearchState(deque<BucketState>& states);

void SearchStateOnAction(deque<BucketState>& states, BucketState& current, int from, int to)
{
    if(IsCurrentActionValid(current, from, to))
    {
        BucketState next;
         /*从'b4?from到'b5?to倒'b5?水'cb?，'a3?如'c8?果'b9?成'b3?功'b9?，'a3?返'b7?回'bb?倒'b5?水'cb?后'ba?的'b5?状'd7?态'cc?*/
        bool bDump = current.DumpWater(from, to, next);
        if(bDump && !IsProcessedState(states, next))
        {
            states.push_back(next);
            SearchState(states);
            states.pop_back();
        }
    }
}

void SearchState(deque<BucketState>& states)
{
    BucketState current = states.back(); /*每'c3?次'b4?都'b6?从'b4?当'b5?前'c7?状'd7?态'cc?开'bf?始'ca?*/
    if(current.IsFinalState())
    {
        PrintResult(states);
        return;
    }

    /*使'ca?用'd3?两'c1?重'd6?循'd1?环'bb?排'c5?列'c1?组'd7?合'ba?种'd6?倒'b5?水'cb?状'd7?态'cc?*/
    for(int j = 0; j < buckets_count; ++j)
    {
        for(int i = 0; i < buckets_count; ++i)
        {
            SearchStateOnAction(states, current, i, j);
        }
    }
}


int main(int argc, char* argv[])
{
    deque<BucketState> states;
    BucketState init;

    states.push_back(init);
    SearchState(states);

    assert(states.size() == 1); /*穷'c7?举'be?结'bd?束'ca?后'ba?states应'd3?该'b8?还'bb?是'ca?只'd6?有'd3?一'd2?个'b8?初'b3?始'ca?状'd7?态'cc?*/

    return 0;
}                                                                                                                                                
