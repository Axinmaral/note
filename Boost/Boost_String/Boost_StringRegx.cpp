#include <boost/regex.hpp>
#include <locale>
#include <iostream>

int main()
{
  std::string s = "Boris Schäling";
  boost::regex expr("\\w+\\s\\w+");
  std::cout << boost::regex_match(s, expr) << std::endl;//使用相关正则表达式进行匹配

  boost::smatch what;
  if(boost::regex_search(s, what, expr)) //可用于在字符串中搜索正则表达式, 函数 boost::regex_search() 只用于分类的搜索
  {
    std::cout << what[0] << std::endl;
    std::cout << what[1] << " " << what[2] << std::endl;
  }

  std::string s2 = " Boris Schäling ";
  boost::regex expr2("\\s");
  std::string fmt2("_");
  std::cout << boost::regex_replace(s, expr2, fmt2) << std::endl;

  std::string s3 = "Boris Schäling";
  boost::regex expr3("(\\w+)\\s(\\w+)");
  std::string fmt3("\\2 \\1");
  //std::cout << boost::regex_replace(s3, expr3, fmt3) << std::endl;
  std::cout << boost::regex_replace(s3, expr3, fmt3, boost::regex_constants::format_literal) << std::endl;
}