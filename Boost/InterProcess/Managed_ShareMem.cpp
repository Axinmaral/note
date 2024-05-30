//托管共享内存
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/bind.hpp>
#include <iostream>

void construct_objects(boost::interprocess::managed_shared_memory &managed_shm)
{
  managed_shm.construct<int>("Integer")(99);
  managed_shm.construct<float>("Float")(3.14);
}

void Mutex_func(void)
{
    std::cout << "Enter Mutex_func...." << std::endl;
    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024);
    int *i = managed_shm.find_or_construct<int>("Integer")();
    boost::interprocess::named_mutex named_mutex(boost::interprocess::open_or_create, "mtx");
    named_mutex.lock();
    ++(*i);
    std::cout << *i << std::endl;
    named_mutex.unlock();
}

//using interprocess_mutex
void Mutex_func2(void)
{
    std::cout << "Enter Mutex_func2...." << std::endl;
    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024);
    int *i = managed_shm.find_or_construct<int>("Integer")();
    boost::interprocess::interprocess_mutex  *mutex = managed_shm.find_or_construct<boost::interprocess::interprocess_mutex>("mtx")();
    mutex->lock();
    ++(*i);
    std::cout << *i << std::endl;
    mutex->unlock();
}


void Conditon_func3(void)
{
    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm2", 1024);
    int *i = managed_shm.find_or_construct<int>("Integer")(0);
    boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx");
    boost::interprocess::shared_memory_object::remove("shm2");
}

int main()
{
    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024);
    int *i = managed_shm.construct<int>("Integer")[10](99);
    std::cout << *i << std::endl;
    managed_shm.destroy<int>("Integer");
    std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer");
    std::cout << p.first << std::endl;
    if (p.first)
    {
        std::cout << *p.first << std::endl;
        std::cout << p.second << std::endl;
    }

    boost::interprocess::managed_shared_memory managed_shm2(boost::interprocess::open_or_create, "Nettrix", 1024);
    typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> charAllocator;
    typedef boost::interprocess::basic_string<char, std::char_traits<char>, charAllocator> string;
    string *s = managed_shm2.find_or_construct<string>("String")("Hello!", managed_shm.get_segment_manager());
    s->insert(5, ", world");
    std::cout << *s << std::endl;

    boost::interprocess::shared_memory_object::remove("Nettrix2");
    boost::interprocess::managed_shared_memory managed_shm3(boost::interprocess::open_or_create, "Nettrix2", 1024);
    auto bound_func = boost::bind(construct_objects, boost::ref(managed_shm3));
    managed_shm3.atomic_func(bound_func);
    std::cout << *managed_shm3.find<int>("Integer").first << std::endl;
    std::cout << *managed_shm3.find<float>("Float").first << std::endl;

    Mutex_func();
    Mutex_func2();
    boost::interprocess::shared_memory_object::remove("shm");
    boost::interprocess::shared_memory_object::remove("Nettrix");
    boost::interprocess::shared_memory_object::remove("Highscore");
    return 0;
}