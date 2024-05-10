//可扩展性是指，一个应用程序从新增资源有效地获得好处的能力。
//如果那些执行时间较长的操作不应该阻塞其它操作的话，那么建议使用 Boost.Asio. 由于现今的PC机通常都具有多核处理器，所以线程的应用可以进一步提高一个基于 Boost.Asio 的应用程序的可扩展性。
//两个线程同时执行，执行完毕之后返回
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>

void handler1(const boost::system::error_code &ec)
{
  std::cout << "5 s." << std::endl;
}

void handler2(const boost::system::error_code &ec)
{
  std::cout << "5 s." << std::endl;
}

//第一种方式：同时绑定到相同的service上
boost::asio::io_service io_service;

//第二种方式：绑定在不同的service上
boost::asio::io_service io_service1;
boost::asio::io_service io_service2;

void run()
{
    io_service.run();
}

void run1()
{
    io_service1.run();
}

void run2()
{
    io_service2.run();
}

int main()
{
  boost::asio::deadline_timer timer1(io_service1, boost::posix_time::seconds(5));
  timer1.async_wait(handler1);
  std::cout << "run here 01.." << std::endl;
  boost::asio::deadline_timer timer2(io_service2, boost::posix_time::seconds(5));
  timer2.async_wait(handler2);
  std::cout << "run here 02.." << std::endl;

  boost::thread thread1(run1);
  boost::thread thread2(run2);
  thread1.join();
  thread2.join();
}