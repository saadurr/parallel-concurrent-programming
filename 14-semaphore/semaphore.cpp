#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

class Semaphore
{
public:
    Semaphore(unsigned long initCount) : m_Count(initCount)
    {}
    void Acquire()
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        while(!m_Count)
            m_CV.wait(lock);
        
        m_Count--;
    }
    void Release()
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        m_Count++;
        lock.unlock();
        m_CV.notify_one();
    }
private:
    std::mutex m_Mutex;
    std::condition_variable m_CV;
    unsigned long m_Count;
};

Semaphore semaphore(4);

void SemaphoreTest(int id)
{
    semaphore.Acquire();
    printf("Semaphore has been acquired by thread %d...\n", id);
    srand(id);
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000 + 1000));
    printf("Thread %d has completed its work and is releasing semaphore....\n", id);
    semaphore.Release();
}

int main()
{
    std::thread threads[10];

    for(int i = 0; i < 10; ++i)
        threads[i] = std::thread(SemaphoreTest, i);
    
    for(int i = 0; i < 10; ++i)
        threads[i].join();

    std::cin.get();
    return 0;
}