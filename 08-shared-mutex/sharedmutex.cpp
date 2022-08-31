#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <array>
#include <shared_mutex>

// Shared mutex can be used when multiple threads are reading the same resource.
// Also called read-writer lock - allows for multiple to read OR single thread to write to the resource.
// available in C++ 17 and later

char WEEKDAYS[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int today = 0;
std::shared_mutex marker;

void CalendarReader(const int id)
{
    for (int i = 0; i < 7; i++)
    {
        marker.lock_shared();
        std::cout << "Reader Thread with ID " << id << " sees today is " << WEEKDAYS[today] << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        marker.unlock_shared();
    }
}

void CalendarWriter(const int id)
{
    for (int i = 0; i < 7; i++)
    {
        marker.lock();
        today = (today + 1) % 7;
        std::cout << "Writer Thread with ID " << id << " updates today's date to " << WEEKDAYS[today] << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        marker.unlock();
    }
}

int main()
{
    std::array<std::thread, 10> readers;
    for(unsigned int i =0; i < readers.size(); i++)
        readers[i] = std::thread(CalendarReader,i);

    std::array<std::thread, 2> writers;
    for(unsigned int i = 0; i < writers.size(); i++)
        writers[i] = std::thread(CalendarWriter,i);


    for (unsigned int i =0; i < readers.size(); i++)
        readers[i].join();
    
    for (unsigned int i =0; i < writers.size(); i++)
        writers[i].join();

    std::cin.get();
    return 0;
}