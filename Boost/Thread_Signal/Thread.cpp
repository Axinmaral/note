#include <boost/thread.hpp>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

#define MUTEX_TEST 0
#define SHOW_PID 0
#define MUTEX_LOCK_GUARD 1

void wait(int seconds)
{
    boost::this_thread::sleep_for(boost::chrono::milliseconds(1000*seconds));
}

void thread()
{
    std::cout <<"sub process thread id: "<< boost::this_thread::get_id() << std::endl;
    try
    {
        for(int i = 0; i <= 5; i++)
        {
            wait(1);
            std::cout << "sub thread is created, count = " << i << std::endl;
        }
    }
    catch(boost::thread_interrupted&)
    {
        std::cout << "Sub thread exit interrupted!" << std::endl;
    }
}

//mutex测试demo
boost::mutex mutex;

void thread2()
{
  for (int i = 0; i < 5; ++i)
  {
    wait(1);
    mutex.lock();
    std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl;
    mutex.unlock();
  }
}

//lock_guard测试demo
void thread3()
{
  for (int i = 0; i < 5; ++i)
  {
    wait(1);
    boost::lock_guard<boost::mutex> lock(mutex);
    std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl;
  }
}

#if SHOW_PID
int main()
{
    boost::thread t(thread);
    std::cout <<"main process thread id: "<< boost::this_thread::get_id() << std::endl;
    std::cout << "In main Process!" << std::endl;
    std::cout << "using cpu core: " << boost::thread::hardware_concurrency() << std::endl;
    wait(3);
    t.interrupt();
    //t.join();
    return 0;
}
#endif

#if MUTEX_TEST
int main()
{
    boost::thread t1(thread2);
    boost::thread t2(thread2);
    pause();
    //wait(100);
    //t1.join();
    //t2.join();
    return 0;
}
#endif

#if MUTEX_LOCK_GUARD
int main()
{
    boost::thread t1(thread3);
    boost::thread t2(thread3);
    pause();
    //wait(100);
    //t1.join();
    //t2.join();
    return 0;
}
#endif