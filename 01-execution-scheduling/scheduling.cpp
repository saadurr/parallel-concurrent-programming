#include <iostream>
#include <thread>
#include <chrono>

bool keepCounting = true;

void Counter(const char *name)
{
    unsigned int count = 0;

    while (keepCounting)
        count++;

    std::cout << name << " Thread has counted " << count << " .\n";
}

int main()
{
    std::thread worker1(Counter, "Thread1");
    std::thread worker2(Counter, "Thread2");

    std::cout << "Thread1 and Thread2 are working together\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    keepCounting = false;

    worker1.join();
    worker2.join();
    
    std::cin.get();
    return 0;
}