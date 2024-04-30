#include <boost/tokenizer.hpp>
#include <string>
#include <iostream>

int main()
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    std::string s = "Boost C++ Libraries";
    //boost::char_separator<char> sep(" ");//如果将+号做为第二个参数，则效果一样boost::char_separator<char> sep(" ", "+");在第二个参数指定了需要显示的分隔符。 在不提供此参数的情况下，将不显示任何分隔符
    boost::char_separator<char> sep(" ", "+", boost::keep_empty_tokens);
    //tokenizer tok(s);
    tokenizer tok(s, sep);
    for(tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    typedef boost::tokenizer<boost::char_separator<wchar_t>, std::wstring::const_iterator, std::wstring> tokenizer2;
    std::wstring s2 = L"Boost C++ libraries";
    boost::char_separator<wchar_t> sep2(L" ");
    tokenizer2 tok2(s2, sep2);
    for(tokenizer2::iterator it2 = tok2.begin(); it2 != tok2.end(); ++it2)
    {
        std::wcout << *it2 << std::endl;
    }

    typedef boost::tokenizer<boost::escaped_list_separator<char> > tokenizer3;//boost::escaped_list_separator 类用于读取由逗号分隔的多个值，这个格式的文件通常称为 CSV （comma separated values，逗号分隔文件），它甚至还可以处理双引号以及转义序列
    std::string s3 = "Boost,\"C++ libraries\"";
    tokenizer3 tok3(s3);
    for(tokenizer3::iterator it3 = tok3.begin(); it3 != tok3.end(); ++it3)
    {
        std::cout << *it3 << std::endl;
    }

    typedef boost::tokenizer<boost::offset_separator> tokenizer4;
    std::string s4 = "Boost C++ libraries";
    int offsets[] = { 5, 5, 9 };
    boost::offset_separator sep4(offsets, offsets+3);
    tokenizer4 tok4(s4, sep4);
    for(tokenizer::iterator it4 = tok4.begin(); it4 != tok4.end(); ++it4)
    {
        std::cout << *it4 << std::endl;
    }
    return 0;
}
