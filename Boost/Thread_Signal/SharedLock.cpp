#include <boost/thread.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void wait(int seconds)
{
    boost::this_thread::sleep_for(boost::chrono::milliseconds(1000*seconds));
}

boost::shared_mutex mutex;
std::vector<int> random_number;

void fill()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    for (int i = 0; i < 10; ++i)
    {
        boost::unique_lock<boost::shared_mutex> lock(mutex);
        random_number.push_back(std::rand());
        lock.unlock();
        wait(1);
    }
}

void print()
{
    for(int i = 0; i < 10; ++i)
    {
        wait(1);
        boost::shared_lock<boost::shared_mutex> lock(mutex);
        std::cout << random_number.back() << std::endl;
        //lock.unlock();
    }
}


int sum = 0;

void count()
{
  for (int i = 0; i < 10; ++i)
  {
    wait(1);
    boost::shared_lock<boost::shared_mutex> lock(mutex);
    sum += random_number.back();
    //lock.unlock();
  }
}


int main()
{
  boost::thread t1(fill);
  boost::thread t2(print);
  boost::thread t3(count);

  std::cout << "Sum: " << sum << std::endl;
  wait(200);
}