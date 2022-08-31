#include <iostream>
#include <thread>
#include <mutex>

//Abandoned lock occurs when a thread exits prematurely and does not releases its mutex.
//scoped locks can help in such situations by automatically releasing the mutex when thread exits.

int count = 5000;

void Decrement(std::mutex& lock)
{
    while(count > 0)
    {
        std::scoped_lock(lock);
        
        if(count)
            count--;
        
        if(count == 10)
        {
            printf("This thread has decremented enough times.....\n");
            break;
        }
    }
}


int main()
{
    std::mutex lock;

    std::thread worker1(Decrement, std::ref(lock));
    std::thread worker2(Decrement, std::ref(lock)); //if order is swapped, then it will result in a deadlock

    worker1.join();
    worker2.join();

    printf("The worker threads have finished working....\n");

    std::cin.get();
    return 0;
}