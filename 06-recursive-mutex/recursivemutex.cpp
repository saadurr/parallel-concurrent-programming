#include <iostream>
#include <thread>
#include <mutex>

// Reentrant mutex or recursive mutex can be locked multiple times but needs to be unlocked equal number of times after.

unsigned int counterShips = 0;
unsigned int counterBoats = 0;

std::recursive_mutex countLock;

void IncrementShips()
{
    countLock.lock();
    counterShips++;
    countLock.unlock();
}

void IncrementBoats()
{
    countLock.lock();
    counterBoats++;
    IncrementShips();  //---> Calling this function here with simple mutex 
                       //     would result in a nested lock which would lock the mutex twice, resulting in deadlock.
    countLock.unlock();
}

void Counter()
{
    for (int i = 0; i < 10000; i++)
    {
        IncrementShips();
        IncrementBoats();
    }
}

int main()
{
    std::thread worker1(Counter);
    std::thread worker2(Counter);

    worker1.join();
    worker2.join();

    std::cout << "The total count of ships is: " << counterShips << std::endl;
    std::cout << "The total count of boats is: " << counterBoats << std::endl;

    std::cin.get();
    return 0;
}