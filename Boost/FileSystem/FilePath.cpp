#include <boost/filesystem.hpp>
#include <iostream>

int main()
{
  boost::filesystem::path p("/home/bmc/Project/Boost_Project/note/C++");
  for(boost::filesystem::path::iterator it = p.begin(); it != p.end(); ++it)
  {
      std::cout << *it << std::endl;
  }
  boost::filesystem::path p("C:\\");

  try
  {
    boost::filesystem::file_status s = boost::filesystem::status(p);
    std::cout << boost::filesystem::is_directory(s) << std::endl;
  }
  catch (boost::filesystem::filesystem_error &e)
  {
    std::cerr << e.what() << std::endl;
  }

  try
  {
    std::cout << boost::filesystem::file_size(p) << std::endl;
  }
  catch (boost::filesystem::filesystem_error &e)
  {
    std::cerr << e.what() << std::endl;
  }

  try
  {
    std::time_t t = boost::filesystem::last_write_time(p);
    std::cout << std::ctime(&t) << std::endl;
  }
  catch (boost::filesystem::filesystem_error &e)
  {
    std::cerr << e.what() << std::endl;
  }

  try
  {
    if (boost::filesystem::create_directory(p))
    {
      boost::filesystem::rename(p, "C:\\Test2");
      boost::filesystem::remove("C:\\Test2");
    }
  }
  catch (boost::filesystem::filesystem_error &e)
  {
    std::cerr << e.what() << std::endl;
  }

  try
  {
    std::cout << boost::filesystem::complete("photo.jpg") << std::endl;
  }
  catch (boost::filesystem::filesystem_error &e)
  {
    std::cerr << e.what() << std::endl;
  }
}