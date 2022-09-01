#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

// Condition variable is used to minimize CPU cycles wasted in threads repeatedly checking if the other threads have completed
// tasks before this thread can acquire the mutex.

// condition variable when associated with mutex forms a construct called monitor.

// There are three main steps: wait, signal, broadcast

int counter = 10;
std::mutex countLock;
std::condition_variable lockTaken;

void Decrementer(int id)
{
    int released = 0;
    
    while(counter > 0)
    {
        std::unique_lock<std::mutex> lock(countLock);
        if((id == counter % 2) && (counter > 0))
            counter--;
        else
            released++;
    }

    printf("Thread ID %d took the mutex and released it %u times.\n", id, released);
}

void DecrementerWithCondition(int id)
{
    int released = 0;
    
    while(counter > 0)
    {
        std::unique_lock<std::mutex> lock(countLock);
        
        while((id != counter % 5) && (counter > 0))
        {
            released++;
            lockTaken.wait(lock);
        }
        if(counter > 0)
        {
            counter--;
            lock.unlock();
            lockTaken.notify_all();
        }
    }

    printf("Thread ID %d took the mutex and released it %u times.\n", id, released);
}


int main()
{
    std::thread threads[5];

    for (int i = 0; i < 5; i++) 
        threads[i] = std::thread(DecrementerWithCondition, i);
    
    for (auto& t : threads) 
        t.join();

    std::cin.get();
    return 0;
}