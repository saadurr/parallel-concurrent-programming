#include <iostream>
#include <thread>
#include <mutex>

unsigned int count = 0;
std::mutex counterLock;

void SharedCounter()
{
    counterLock.lock();
    for(int i = 0; i < 100000; ++i)
        count++;
    counterLock.unlock();
}

int main()
{
    std::thread worker1(SharedCounter);
    std::thread worker2(SharedCounter);

    worker1.join();
    worker2.join();

    std::cout << "The total count by both worker functions is " << count << std::endl;

    std::cin.get();
    return 0;
}