#include <iostream>
#include <thread>
#include <queue> //this library is not thread-safe
#include <mutex>
#include <condition_variable>

class ServingLine
{
public:
    void ServeValue(int i)
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        m_ValueQueue.push(i);
        lock.unlock();
        m_ValueServed.notify_one();
    }

    int TakeValue()
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        while(m_ValueQueue.empty())
        {
            m_ValueServed.wait(lock);
        }
        int value = m_ValueQueue.front();
        m_ValueQueue.pop();
        return value;
    }

private:
    std::queue<int> m_ValueQueue;
    std::mutex m_Mutex;
    std::condition_variable m_ValueServed;
};

ServingLine servingLine = ServingLine();

void ValueProducer()
{
    for (int i = 0; i < 100000; i++)
        servingLine.ServeValue(1);

    servingLine.ServeValue(-1);
    printf("Producer is done serving values...\n\n");
}

void ValueConsumer()
{
    int numValueServed = 0;

    while (true)
    {
        int value = servingLine.TakeValue();
        if (value == -1)
        {
            printf("Consumer consumed %d number of values.\n", numValueServed);
            servingLine.ServeValue(-1);
            return;
        }
        else
            numValueServed += value;
    }
}

int main()
{
    std::thread worker1(ValueProducer);
    std::thread worker2(ValueConsumer);
    std::thread worker3(ValueConsumer);

    worker1.join();
    worker2.join();
    worker3.join();

    std::cin.get();
    return 0;
}