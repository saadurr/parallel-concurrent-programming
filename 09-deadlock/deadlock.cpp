#include <iostream>
#include <thread>
#include <mutex>

int count = 5000;

void Decrement(std::mutex& firstMutex, std::mutex& secondMutex)
{
    while(count > 0)
    {
        firstMutex.lock();
        secondMutex.lock();
        
        if(count)
            count--;
        
        firstMutex.unlock();
        secondMutex.unlock();
    }
}

void DecrementWithScopedLock(std::mutex& firstMutex, std::mutex& secondMutex)
{
    while(count > 0)
    {
        std::scoped_lock(firstMutex,secondMutex);
        
        if(count)
            count--;
    }
}


int main()
{
    std::mutex firstMutex, secondMutex;

    std::thread worker1(Decrement, std::ref(firstMutex), std::ref(secondMutex));
    std::thread worker2(Decrement, std::ref(firstMutex), std::ref(secondMutex)); //if order is swapped, then it will result in a deadlock

    worker1.join();
    worker2.join();

    printf("The worker threads have finished working....\n");

    std::cin.get();
    return 0;
}