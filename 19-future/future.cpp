#include <iostream>
#include <thread>
#include <future>


int NumberProcessor()
{
    printf("Number processor function is crunching numbers...\n\n");
    std::this_thread::sleep_for(std::chrono::seconds(6)); // sleep for three seconds
    return 99;
}

int main() 
{
    printf("The main function is requesting Number Processor to return a result...\n");
    
    std::future<int> result = std::async(std::launch::async, NumberProcessor); //the return value is a future
    
    for(int i = 0; i < 5; ++i)
    {
        printf("The main function is performing other work while the Number Processor function is working....\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
    }

    printf("\n\nThe Number Processor function has responded with %d", result.get());

    std::cin.get();
    return 0;
}