#include <iostream>
#include <boost/asio.hpp>

//Thread pool is like a todo list for threads.

void ThreadFunction(int taskID)
{
    printf("Thread %d performed task with ID %d.\n", std::this_thread::get_id(), taskID);
}

int main()
{
    boost::asio::thread_pool pool(4);

    for(int i = 0; i < 100; ++i)
    {
        boost::asio::post(pool, [i](){ThreadFunction(i);});
    }

    pool.join();

    std::cin.get();
    return 0;
}