#ifndef __BUCKET_STATE_H__
#define __BUCKET_STATE_H__

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

#endif //__BUCKET_STATE_H__
