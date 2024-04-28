//为了封装函数指针，Boost.Function 提供了一个名为 boost::function 的类。 它定义于 boost/function.hpp
#include <boost/function.hpp>
#include <iostream>
#include <cstdlib>
#include <cstring>


struct world
{
    void hello(std::ostream &os)
    {
        os << "hello world" << std::endl;
    }
};

int main()
{
  boost::function<int (const char*)> f = std::atoi;
  std::cout << f("1609") << std::endl;
  f = std::strlen;
  std::cout << f("1609") << std::endl;

  boost::function<void (world *, std::ostream &)> g = &world::hello;
  world w;
  g(&w, std::cout);
}