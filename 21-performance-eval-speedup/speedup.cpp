/**
 * Measure the speedup of a parallel algorithm
 */
#include <future>
#include <chrono>

unsigned long long SequentialSum(unsigned int lo , unsigned int hi) 
{
    unsigned long long sum = 0;
    for (auto i=lo; i<hi; i++) {
        sum += i;
    }
    return sum;
}

unsigned long long ParallelSum(unsigned int lo , unsigned int hi, unsigned int depth=0) 
{
    if (depth > 3) 
    { // base case threshold
        unsigned long long sum = 0;
        for (auto i=lo; i<hi; i++) 
        {
            sum += i;
        }
        return sum;
    } 
    else 
    {  // divide and conquer
        auto mid = (hi + lo) / 2; // middle index for splitting
        auto left = std::async(std::launch::async, ParallelSum, lo, mid, depth+1);
        auto right = ParallelSum(mid, hi, depth+1);
        return left.get() + right;
    }
}

int main() 
{
    const int TOTALEVALRUNS = 10;
    const int SUMVALUE = 100000000;

    printf("Evaluating Sequential Implementation...\n");\
    std::chrono::duration<double> sequentialTime(0);
    auto sequential_result = SequentialSum(0, SUMVALUE); // "warm up"
    for (int i=0; i< TOTALEVALRUNS; i++) 
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        SequentialSum(0, SUMVALUE);   
        sequentialTime += std::chrono::high_resolution_clock::now() - start_time;
    }
    sequentialTime /= TOTALEVALRUNS;
	
    printf("Evaluating Parallel Implementation...\n");
    std::chrono::duration<double> parallelTime(0);
    auto parallelResult = ParallelSum(0, SUMVALUE); // "warm up"
    for (int i=0; i<TOTALEVALRUNS; i++) 
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        ParallelSum(0, SUMVALUE);   
        parallelTime += std::chrono::high_resolution_clock::now() - start_time;
    }
    parallelTime /= TOTALEVALRUNS;

    // display sequential and parallel results for comparison
    if (sequential_result != parallelResult) 
    {
        printf("ERROR: Result mismatch!\n  Sequential Result = %lld\n  Parallel Result = %lld\n", sequential_result, parallelResult);
    }
    printf("Average Sequential Time: %.1f ms\n", sequentialTime.count()*1000);
    printf("  Average Parallel Time: %.1f ms\n", parallelTime.count()*1000);
    printf("Speedup: %.2f\n", sequentialTime/parallelTime);
    printf("Efficiency %.2f%%\n", 100*(sequentialTime/parallelTime)/std::thread::hardware_concurrency());
}