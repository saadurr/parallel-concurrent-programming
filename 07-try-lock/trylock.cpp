#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// Try lock allows threads to do other work until the mutex is busy, without having the threads go into blocking state

unsigned int numItemsToWrite = 0;
std::mutex writeLock;

void AddItemsNormally(const char *name)
{
    int numItemsToAdd = 0;
    while (numItemsToWrite <= 20)
    {
        if (numItemsToAdd)
        {
            writeLock.lock();
            numItemsToWrite += numItemsToAdd;
            std::cout << name << " added " << numItemsToAdd << " items to notepad.\n";
            numItemsToAdd = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            writeLock.unlock();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); //looking for items or doing the task
            numItemsToAdd++; 
            std::cout << name << " found something to add...\n";
        }
    }
}

void AddItemsTry(const char *name)
{
    int numItemsToAdd = 0;
    while (numItemsToWrite <= 20)
    {
        if (numItemsToAdd && writeLock.try_lock())
        {
            numItemsToWrite += numItemsToAdd;
            std::cout << name << " added " << numItemsToAdd << " items to notepad.\n";
            numItemsToAdd = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            writeLock.unlock();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); //looking for items or doing the task
            numItemsToAdd++; 
            std::cout << name << " found something to add...\n";
        }
    }
}

void NormalLock()
{
    auto startTime = std::chrono::steady_clock::now();

    std::thread worker1(AddItemsNormally, "Thread Worker 1");
    std::thread worker2(AddItemsNormally, "Thread Worker 2");

    worker1.join();
    worker2.join();

    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
    std::cout << "Elapsed Time: " << elapsedTime/1000.0 << " seconds\n";
}

void TryLock()
{
    auto startTime = std::chrono::steady_clock::now();

    std::thread worker1(AddItemsTry, "Thread Worker 1");
    std::thread worker2(AddItemsTry, "Thread Worker 2");

    worker1.join();
    worker2.join();

    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
    std::cout << "Elapsed Time: " << elapsedTime/1000.0 << " seconds\n";
}

int main()
{
    std::cout << "Using Normal Lock...\n\n";
    NormalLock();

    std::cout << "\n\nUsing Try Lock...\n\n";
    TryLock();

    std::cin.get();
    return 0;
}