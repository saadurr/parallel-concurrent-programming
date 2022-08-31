#include <iostream>
#include <thread>
#include <mutex>

int count = 5000;

void Decrement(std::mutex &firstMutex, std::mutex &secondMutex)
{
    while (count > 0)
    {
        firstMutex.lock();
        if (!secondMutex.try_lock())
        {
            firstMutex.unlock();
            std::this_thread::yield(); //causes the thread to wait a little before trying again
        }
        else
        {
            if (count)
                count--;

            firstMutex.unlock();
            secondMutex.unlock();
        }
    }
}

int main()
{
    std::mutex firstMutex, secondMutex;

    std::thread worker1(Decrement, std::ref(firstMutex), std::ref(secondMutex));
    std::thread worker2(Decrement, std::ref(secondMutex), std::ref(firstMutex)); // deadlock
    std::thread worker3(Decrement, std::ref(firstMutex), std::ref(secondMutex));
    std::thread worker4(Decrement, std::ref(secondMutex), std::ref(firstMutex)); // deadlock

    worker1.join();
    worker2.join();
    worker3.join();
    worker4.join();

    printf("The worker threads have finished working....\n");

    std::cin.get();
    return 0;
}