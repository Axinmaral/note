//Boost.Format 库可以作为定义在文件 cstdio 中的函数 std::printf() 的替代
#include <boost/format.hpp>
#include <iostream>

int main()
{
    std::cout << boost::format("%1%.%2%.%3%") % 16 % 9 % 2008 << std::endl; //16.9.2008
    std::cout << boost::format("%2%/%1%/%3%") % 16 % 9 % 2008 << std::endl;
    std::cout << boost::format("%1% %2% %1%") % boost::io::group(std::showpos, 99) % 100 << std::endl;//+99 100 +99
    std::cout << boost::format("%|1$+| %2% %1%") % 99 % 100 << std::endl;//+99 100 99
    std::cout << boost::format("%+d %d %d") % 99 % 100 % 99 << std::endl;
    std::cout << boost::format("%+s %s %s") % 99 % 100 % 99 << std::endl;
}
