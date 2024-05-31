//Boost.DateTime模块
#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

int main()
{
    boost::gregorian::date date(2021, 1, 23);
    std::cout << date.year() << std::endl;
    std::cout << date.month() << std::endl;
    std::cout << date.day() << std::endl;
    std::cout << date.day_of_week() << std::endl;
    std::cout << date.day_of_year() << std::endl;

    boost::gregorian::date date2 = boost::gregorian::day_clock::universal_day();
    std::cout << date2.year() << std::endl;
    std::cout << date2.month() << std::endl;
    std::cout << date2.day() << std::endl;

    date2 = boost::gregorian::date_from_iso_string("20210501");
    std::cout << date2.year() << std::endl;
    std::cout << date2.month() << std::endl;
    std::cout << date2.day() << std::endl;

    //两者时间的差距-day的差距
    boost::gregorian::date d1(2021, 1, 23);
    boost::gregorian::date d2(2021, 9, 15);
    boost::gregorian::date_duration dd = d2 - d1;
    std::cout << dd.days() << std::endl;

    boost::gregorian::date_duration dd2(4);
    std::cout << dd2.days() << std::endl;
    boost::gregorian::weeks ws(4);
    std::cout << ws.days() << std::endl;
    boost::gregorian::months ms(4);
    std::cout << ms.number_of_months() << std::endl;
    boost::gregorian::years ys(4);
    std::cout << ys.number_of_years() << std::endl;

    boost::gregorian::date d(2009, 1, 30);
    boost::gregorian::months mss(1);
    boost::gregorian::date d23 = d + mss;
    std::cout << d23 << std::endl;
    boost::gregorian::date d33 = d23 - mss;
    std::cout << d33 << std::endl;
}