#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <utility>

void f1(int n){
    std::cout << "RUNING THREAD ID : " << std::this_thread::get_id() << std::endl;
    for(int i = 0 ; i < 3; ++i){
        std::cout << "Thread 1 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void f2(int& n){
    std::cout << "RUNING THREAD ID : " << std::this_thread::get_id() << std::endl;
    for(int i = 0 ; i < 3; ++i){
        std::cout << "Thread 2 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

class foo
{
    public:
        int n = 0;
        void bar(){
            std::cout << "RUNING THREAD ID : " << std::this_thread::get_id() << std::endl;
            for(int i = 0 ; i < 3; ++i){
                std::cout << "Thread 3 executing\n";
                ++n;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
        foo(){}
        foo(const foo& other){
            *this = other;
            std::cout << "Call foo copy constructor" << std::endl;
        }

};

class baz
{
    public:
        int n = 0;
        void operator()(){
            std::cout << "RUNING THREAD ID : " << std::this_thread::get_id() << std::endl;
            for(int i = 0 ; i < 3; ++i){
                std::cout << "Thread 4 executing\n";
                ++n;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
        baz(){}
        baz(const baz& other){
            *this = other;
            std::cout << "Call baz copy constructor" << std::endl;
        }
};

int main(){
    int n1 = 0;
    int n2 = 0;
    foo f;
    baz b;

    std::thread t1; // t1此时不是一个线程
    std::thread t2(f1, n1); // 按值传递开启线程
    std::thread t3(f2, std::ref(n2)); // 按引用传递开启线程
    std::thread t4(std::move(t3));// 将t3移到t4上，t3此刻不是线程了
    // 下面开启一个 对象 的某个函数的线程
    std::thread t5(&foo::bar, &f); // 在f上运行foo::bar开启线程
    std::thread t6(b); // 以 b 的一个副本，用operator()开启线程



    t2.join();
    t4.join();
    t5.join();
    t6.join();
    std::cout << "Final value of n1 is : " << n1 << "\n";
    std::cout << "Final value of n2 is : " << n2 << "\n";
    std::cout << "Final value of n of f(foo) : " << f.n << "\n";
    std::cout << "Final value of n of b(baz) : " << b.n << "\n";
    return 0;
}
