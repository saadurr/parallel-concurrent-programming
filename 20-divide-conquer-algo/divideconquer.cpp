/**
 * Recursively sum range of numbers
 */
#include <iostream>
#include <future>

unsigned long long RecursiveSum(unsigned int lo, unsigned int hi, unsigned int depth = 0)
{
    if(depth > 3)
    {
        unsigned long long sum = 0;
        for(int i = lo; i < hi; ++i)
            sum += i;
        
        return sum;
    }
    else
    {
        auto mid = (hi + lo) / 2;
        auto left = std::async(std::launch::async, RecursiveSum, lo, mid, depth+1);
        auto right = RecursiveSum(mid, hi, depth+1);

        return left.get() + right;
    }
}

int main() 
{
    unsigned long long total = RecursiveSum(0, 1000000000);
    printf("Total: %lld\n", total);
}