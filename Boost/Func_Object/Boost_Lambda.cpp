//匿名函数：让代码更紧凑

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> v;
  v.push_back(1);
  v.push_back(3);
  v.push_back(2);

  std::for_each(v.begin(), v.end(), std::cout << boost::lambda::_1 << "\n");

  //除了 boost::lambda::if_then(), Boost.Lambda 还提供了 boost::lambda::if_then_else() 和 boost::lambda::if_then_else_return() 模板函数 - 它们都要求三个参数。
  //另外还提供了用于实现循环、转型操作符，甚至是 throw - 允许 lambda 函数抛出异常 - 的模板函数。
  std::for_each(v.begin(), v.end(), boost::lambda::if_then(boost::lambda::_1 > 2, std::cout << boost::lambda::_1 << "\n"));
}