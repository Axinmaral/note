#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

int main()
{
    boost::interprocess::shared_memory_object shdmem(boost::interprocess::open_or_create, "Hiscore", boost::interprocess::read_write);
    shdmem.truncate(1024);
    std::cout << shdmem.get_name() << std::endl;
    boost::interprocess::offset_t size;
    if(shdmem.get_size(size))
    {
         std::cout << "Size = " << size << std::endl;
    }

    boost::interprocess::mapped_region region(shdmem, boost::interprocess::read_write);
    std::cout << std::hex << "0x" << region.get_address() << std::endl;
    std::cout << std::dec << region.get_size() << std::endl;
    boost::interprocess::mapped_region region2(shdmem, boost::interprocess::read_only);
    std::cout << std::hex << "0x" << region2.get_address() << std::endl;
    std::cout << std::dec << region2.get_size() << std::endl;

    //写入并读取一个数字
    int *i1 = static_cast<int*>(region.get_address());//static_cast与dynamic_cast
    *i1 = 99;
    int *i2 = static_cast<int*>(region2.get_address());
    std::cout << "Read val = " << *i2 << std::endl;

    //remove shared mem
    bool removed1 = boost::interprocess::shared_memory_object::remove("Hiscore");
    std::cout << "Remove result: " << removed1 << std::endl;
}