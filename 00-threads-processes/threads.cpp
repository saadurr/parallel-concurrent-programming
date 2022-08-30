#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h> //API for POSIX operating system

void CPUWaster()
{
    std::cout << "The Process ID for this CPU Waster is: " << getpid() << "\n";
    std::cout << "The Thread ID for this CPU Waster is: " << std::this_thread::get_id() << "\n";

    // Infinite loop
    while(true)
        continue;
}

int main()
{
    //using namespace std::literals::chrono_literals; //in C++ 14
    
    std::cout << "The Process ID for this Main is: " << getpid() << "\n";
    std::cout << "The Thread ID for this CPU Waster is: " << std::this_thread::get_id() << "\n";

    std::thread worker1(CPUWaster);
    std::thread worker2(CPUWaster);

    while(true)
        std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cin.get();
    return 0;
}