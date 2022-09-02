#include <iostream>
#include <thread>
#include <mutex>

// The output of this program keeps on changing because there is no specific order in which the threads will call the functions.

unsigned int count = 1;
std::mutex m;

void ProcessWork(unsigned long workUnits) // some cpu intensive worker function
{
    unsigned long x = 0;
    for(unsigned long i = 0; i < workUnits*1000000; ++i)
        x++;
}

void Multiplier()
{
    ProcessWork(1);
    std::scoped_lock<std::mutex> lock(m);
    count *= 2;
    printf("Multipler function has DOUBLED the count...\n");
}

void Adder()
{
    ProcessWork(1);
    std::scoped_lock<std::mutex> lock(m);
    count += 3;
    printf("Adder function has ADDED 3 to the count...\n");
}

int main()
{
    std::thread threads[10];

    for(int i = 0; i < 10; i+=2)
    {
        threads[i] = std::thread(Multiplier);
        threads[i+1] = std::thread(Adder);
    }

    for (int i = 0; i < 10; ++i)
        threads[i].join();
    
    printf("\n\nThe total count is %d .", count);

    std::cin.get();
    return 0;
}