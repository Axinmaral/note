#include <boost/thread.hpp>
#include <iostream>
#include <cstdlib> // 引入标准库的随机数生成函数
#include <ctime> // 引入标准库的时间函数

/**
 * 初始化一个用于生成随机数的线程特定变量。
 * 当线程首次访问该变量时，它将被初始化为true。
 * 同时，使用当前的时间作为随机数种子，以保证每次运行时生成的随机数序列不同。
 */
void init_number_generator()
{
  static boost::thread_specific_ptr<bool> tls; // 声明一个线程特定的布尔指针变量

  // 检查当前线程是否已经初始化过该变量
  if(!tls.get())
  {
    tls.reset(new bool(true)); // 如果没有，则初始化该变量为true
  }

  // 检查变量是否已被设置为生成随机数的状态
  if (!*tls)
  {
    *tls = true; // 设置状态为true，表示该线程已经开始生成随机数
    std::srand(static_cast<unsigned int>(std::time(0))); // 使用当前时间作为随机数种子
  }
}

boost::mutex mutex;

void random_number_generator()
{
  init_number_generator();
  int i = std::rand();
  boost::lock_guard<boost::mutex> lock(mutex);
  std::cout << i << std::endl;
}

int main()
{
  boost::thread t[3];

  for (int i = 0; i < 3; ++i)
    t[i] = boost::thread(random_number_generator);

  for (int i = 0; i < 3; ++i)
    t[i].join();
}