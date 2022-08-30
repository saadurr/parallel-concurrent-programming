#include <iostream>
#include <thread>
#include <chrono>

void CollectGarbage()
{
    while(true)
    {
        std::cout << "I am collecting garbage...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    std::thread worker(CollectGarbage);
    worker.detach();

    for (int i = 0; i < 3; i++)
    {
        std::cout << "Main thread is working....\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }

    std::cout << "Main thread is done...\n";

    std::cin.get();
    return 0;
}