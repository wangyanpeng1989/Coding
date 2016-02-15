#ifndef __MONkMONSTER_H__
#define __MONkMONSTER_H__

const int buckets_count = 3;

struct Action
{
    int from;
    int to;
    int water;
};

struct BucketState
{
    BucketState();
    BucketState(const int *buckets);
    BucketState(const BucketState& state);
    BucketState& operator=(const BucketState& state);
    bool IsSameState(const BucketState& state) const;
    void SetAction(int w, int f, int t);
    void SetBuckets(const int *buckets);
    void GetBuckets(int *buckets) const;                      
    bool IsBucketEmpty(int bucket);
    bool IsBucketFull(int bucket);
    void PrintStates();
    bool IsFinalState();
    bool DumpWater(int from, int to, BucketState& next);

    int bucket_s[buckets_count];
    Action curAction;
};

typedef enum BOAT_LOCATION_S 
{
	LOCAL = 0;
	REMOTE;
}BOAT_LOCATION;

struct ItemState
{
	int local_monster;
	int local_monk;
	int remote_monster;
	int remote_monk;
	BOAT_LOCATION boat;	//local or remote
};

#endif //__MONKMONSTER_H__
