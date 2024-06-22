#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <iostream>


int main()
{
    typedef boost::tuple<std::string, std::string> person;
    person p("Boris", "Akabela");
    std::cout << p << std::endl;

    typedef boost::tuple<std::string, std::string, int> person2;
    person2 p2("Boris", "Homoka", 55);
    std::cout << p2 << std::endl;
    std::cout << boost::make_tuple("Boris", "Schaeling", 43) << std::endl;//类似于std::make_pair()

    std::string s = "Borings";
    std::cout << boost::make_tuple(boost::ref(s), "hahahha", 99) << std::endl;

    std::cout << p.get<0>() << std::endl;
    std::cout << boost::get<0>(p) << std::endl;

    typedef boost::tuple<std::string&, std::string&, int&> Person3;
    std::string firstname = "Borigs";
    std::string secondname = "Akaeasd";
    int shoesize = 39;
    Person3 Sp = boost::tie(firstname, secondname, shoesize);
    secondname = "Becker";
    std::cout << Sp << std::endl;
}