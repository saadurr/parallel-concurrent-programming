#include <iostream>
#include <thread>
#include <atomic>

// Atomic values can be used when a value needs to be accessed by more than one thread and there are no mutex locks in place.
// These values should be used with simple values.

std::atomic<unsigned int> count(0);

void SharedCounter()
{
    for(int i = 0; i < 100000; ++i)
        count++;
}

int main()
{
    std::thread worker1(SharedCounter);
    std::thread worker2(SharedCounter);

    worker1.join();
    worker2.join();

    std::cout << "The total count by both worker functions is " << count.load() << std::endl;

    std::cin.get();
    return 0;
}