#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/any.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <vector>
#include <string>

std::vector<boost::any> vector;

struct output:
public boost::static_visitor<>
{
    template <typename T>
    void operator()(T &t) const
    {
        vector.push_back(t);
    }
};

boost::tuple<std::string, int> func()
{
    return boost::make_tuple("stack overflow", 2009);
}

int main()
{
    std::string errormsg;
    int errcode;

    boost::tie(errormsg, errcode) = func();
    std::cout << "errormsg = " << errormsg << ", errcode = " << errcode << std::endl;

    boost::any a = 1;
    std::cout << boost::any_cast<int>(a) << std::endl;
    a = 3.14;
    std::cout << boost::any_cast<double>(a) << std::endl;
    a = false;
    std::cout << boost::any_cast<bool>(a) << std::endl;

    try
    {
        boost::any b = 1;
        std::cout << boost::any_cast<float>(b) << std::endl;
    }
    catch(const boost::bad_any_cast & e)
    {
        std::cerr << e.what() << '\n';
    }

    if(!a.empty())
    {
        const std::type_info &info = a.type();
        std::cout << info.name() << std::endl;
    }

    boost::variant<double, char, std::string> v;
    v = 3.14;
    std::cout << v << std::endl;
    boost::apply_visitor(output(), v);
    v = 'A';
    std::cout << v << std::endl;
    boost::apply_visitor(output(), v);
    v = "hello, world!";
    std::cout << v << std::endl;
    boost::apply_visitor(output(), v);

}
