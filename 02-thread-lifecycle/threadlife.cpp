#include<iostream>
#include<thread>
#include<chrono>

void Function()
{
    std::cout << "Function 1 has started & waiting for its dependencies to complete...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Function 1 has completed its working...\n";
}

int main()
{
    std::cout << "This is main thread, requesting a worker thread.\n";
    std::thread worker1(Function);
    if(worker1.joinable())
        std::cout << "Worker thread is joinable.\n";
    else
        std::cout << "Worker thread is NOT joinable.\n";

    std::cout << "The main thread is continuing its own work.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if(worker1.joinable())
        std::cout << "Worker thread is joinable.\n";
    else
        std::cout << "Worker thread is NOT joinable.\n";

    std::cout << "The main thread is waiting for worker thread to complete...\n";
    worker1.join();
    if(worker1.joinable())
        std::cout << "Worker thread is joinable.\n";
    else
        std::cout << "Worker thread is NOT joinable.\n";

    std::cout << "The main thread and worker thread are both done....\n";

    std::cin.get();
    return 0;
}