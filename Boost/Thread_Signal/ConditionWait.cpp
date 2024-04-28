#include <boost/thread.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>

boost::mutex mutex;
boost::condition_variable cond;
std::vector<int> random_numbers;
bool data_ready = false; // 新增一个标志以避免假唤醒

// Try-Catch异常处理封装
void joinThread(boost::thread& t) {
    try {
        t.join();  // 等待线程t执行完成
    } catch (const boost::thread_resource_error& e) {
        std::cerr << "线程资源错误：" << e.what() << '\n';
    } catch (const boost::thread_interrupted& e) {
        std::cerr << "线程中断：" << '\n';
    } catch (const std::exception& e) {
        std::cerr << "异常：" << e.what() << '\n';
    } catch (...) {
        std::cerr << "未知错误\n";
    }
}

void fill() {
    std::random_device rd;  // 用于获取随机数种子
    std::mt19937 gen(rd()); // 标准的mersenne_twister_engine
    std::uniform_int_distribution<> dis(1, 100); // 分布在[1, 100]

    for(int i = 0; i < 3; ++i) {
        boost::unique_lock<boost::mutex> lock(mutex);
        random_numbers.push_back(dis(gen));
        data_ready = true; // 设置数据准备好的标志
        cond.notify_one(); // 通知一个等待线程
        cond.wait(lock, []{ return !data_ready; }); // 等待直到数据被消费
    }
}

void print() {
    for(int i = 0; i < 3; ++i) {
        boost::unique_lock<boost::mutex> lock(mutex);
        cond.wait(lock, []{ return data_ready; }); // 等待数据准备好的信号，避免假唤醒
        if (!random_numbers.empty()) {
            std::cout << random_numbers.back() << std::endl;
        }
        data_ready = false; // 重置数据准备好的标志
        cond.notify_one(); // 通知填充线程继续运行
    }
}

int main() {
    boost::thread t1(fill);
    boost::thread t2(print);

    //joinThread(t1);
    //joinThread(t2);
    while(1);
    std::cout << "线程已退出，主线程继续执行。\n";
    return 0;
}