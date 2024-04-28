#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/bind.hpp>

class add: public std::binary_function<int, int, void>
{
public:
  void operator()(int i, int j) const
  {
    std::cout << i + j << std::endl;
  }
};

void print(int i)
{
    std::cout << i << std::endl;
}

void add2(int i, int j)
{
  std::cout << i + j << std::endl;
}

bool compare(int i, int j)
{
  return i > j;
}


int main()
{
    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    std::for_each(v1.begin(), v1.end(), print);

    std::vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);

    std::for_each(v2.begin(), v2.end(), std::bind1st(add(), 10));

    std::vector<int> v3;
    v3.push_back(1);
    v3.push_back(2);
    v3.push_back(3);

    std::for_each(v3.begin(), v3.end(), boost::bind(print, _1));
    std::for_each(v3.begin(), v3.end(), boost::bind(add2, 10, _1));//_1为占位符，其实是这个接口的第一个参数传入

    std::vector<int> v4;
    v4.push_back(1);
    v4.push_back(2);
    v4.push_back(3);

    std::sort(v4.begin(), v4.end(), boost::bind(compare, _1, _2));//降序排列
    std::for_each(v4.begin(), v4.end(), print);

    std::sort(v4.begin(), v4.end(), boost::bind(compare, _2, _1));//升序排列
    std::for_each(v4.begin(), v4.end(), print);
}