//Boost C++弥补std::string中的一些不足
#include <boost/algorithm/string.hpp>
#include <locale>
#include <iostream>
#include <clocale>

//在进入正题之前，有必要先审视下区域设置的问题，本章中提到的很多函数都需要一个附加的区域设置参数。

int main()
{
    //std::locale::global(std::locale("Gemalde"));//还可以设置其他地区--需要跟当前系统的地区匹配
    std::locale loc;
    std::cout << loc.name() << std::endl;

    std::string s1 = "Boring Scheling";
    std::string s2 = "BOARD SCHEMA";
    std::cout << boost::algorithm::to_upper_copy(s1) << std::endl;
    std::cout << boost::algorithm::to_lower_copy(s2) << std::endl;

    std::cout << boost::algorithm::erase_first_copy(s1, "i") << std::endl;
    std::cout << boost::algorithm::erase_nth_copy(s1, "i", 0) << std::endl;
    std::cout << boost::algorithm::erase_last_copy(s1, "i") << std::endl;
    std::cout << boost::algorithm::erase_all_copy(s1, "i") << std::endl;
    std::cout << boost::algorithm::erase_head_copy(s1, 5) << std::endl;
    std::cout << boost::algorithm::erase_tail_copy(s1, 8) << std::endl;

    boost::iterator_range<std::string::iterator> r1 = boost::algorithm::find_first(s1, "Bori");
    std::cout << r1 << std::endl;
    boost::iterator_range<std::string::iterator> r2 = boost::algorithm::find_first(s1, "xyz");
    std::cout << r2 << std::endl;

    std::vector<std::string> v;
    v.push_back("Boring");
    v.push_back("Scheling");
    std::cout << boost::algorithm::join(v, " ") << std::endl;

    return 0;
}