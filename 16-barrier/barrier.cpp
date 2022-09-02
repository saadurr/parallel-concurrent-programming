#include <iostream>
#include <thread>
#include <mutex>
#include <boost/thread/barrier.hpp> //barriers are available in C++ 20 and higher version.


unsigned int count = 1;
std::mutex m;
boost::barrier blocker(10); //takes in the argument of total number of threads

void ProcessWork(unsigned long workUnits) // some cpu intensive worker function
{
    unsigned long x = 0;
    for(unsigned long i = 0; i < workUnits*1000000; ++i)
        x++;
}

void Multiplier()
{
    ProcessWork(1);
    blocker.wait();
    std::scoped_lock<std::mutex> lock(m);
    count *= 2;
    printf("Multipler function has DOUBLED the count...\n");
    
}

void Adder()
{
    ProcessWork(1);
    {
        //to remove the lock as soon as it exits critical section
        std::scoped_lock<std::mutex> lock(m);
        count += 3;
    }
    printf("Adder function has ADDED 3 to the count...\n");
    blocker.wait();
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