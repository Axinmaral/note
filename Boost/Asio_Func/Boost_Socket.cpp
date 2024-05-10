//使用 Boost.Asio 进行异步数据处理的应用程序基于两个概念：I/O 服务和 I/O 对象。 I/O 服务抽象了操作系统的接口，允许第一时间进行异步数据处理，而 I/O 对象则用于初始化特定的操作
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <string>

boost::asio::io_service io_service;
boost::asio::ip::tcp::resolver resolver(io_service);
boost::asio::ip::tcp::socket sock(io_service);
boost::array<char, 4096> buffer;

void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
    if(!ec)
    {
        std::cout << std::string(buffer.data(), bytes_transferred) << std::endl;
        sock.async_read_some(boost::asio::buffer(buffer), read_handler);
    }
}

void connect_handler(const boost::system::error_code &ec)
{
    if(!ec)
    {
        boost::asio::write(sock, boost::asio::buffer("GET / HTTP 1.1\r\nHost: highscore.de\r\n\r\n"));
        sock.async_read_some(boost::asio::buffer(buffer), read_handler);
    }
}

void resolve_handler(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it)
{
    if(!ec)
    {
        sock.async_connect(*it, connect_handler);
    }
}

int main()
{
    boost::asio::ip::tcp::resolver::query query("www.highscore.de", "80");
    resolver.async_resolve(query, resolve_handler);
    io_service.run();
}