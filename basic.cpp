//
// Created by focus on 11.04.2021.
//
#include <iostream>
#include <string>
#include <functional>
#include <thread>
#include <map>
#include <mutex>
#include <future>

using dict_t = std::map<std::string, std::string>;

thread_local int thread_local_static_int = 0;
int static_int = 0;
std::mutex cout_mutex;

std::string foo(dict_t &d) {
    cout_mutex.lock();
    std::cerr << "start foo()" << std::endl;
    cout_mutex.unlock();

    //    ****************************************************
//    throw std::invalid_argument("don't catch exception");

    //    ****************************************************
//    thread_local_static_int = 0;
//    static_int = 0;
//    return "ok";

    //    ****************************************************
    cout_mutex.lock();
    d["aaas"] = "test";
    cout_mutex.unlock();
//    return "ok";

    //    ****************************************************
    std::thread::id id_thread = std::this_thread::get_id();
    cout_mutex.lock();
    std::cout << "foo: " << id_thread << '\n'; // std::endl;
    cout_mutex.unlock();

//    cout_mutex.lock();
//    std::cerr << "foo: " << id_thread << std::endl;
//    cout_mutex.unlock();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    return "ok";
}

void example_thread() {
    try {
        dict_t d1, d2;

//        example 1
//        auto r = foo(std::ref(d1));
//        foo(d1);
//        return;

//      example 2
        std::thread th1(&foo, std::ref(d1));
        std::thread th2(&foo, std::ref(d1));

        if (th1.joinable()) {
            th1.join();
        }
        if (th2.joinable()) {
            th2.join();
        }

    } catch (std::invalid_argument &ex) {
        std::cerr << "oops argument!" << std::endl;
    } catch (...) {
        std::cerr << "oops!" << std::endl;
    }
}

void example_async() {
    try {
        dict_t d1, d2;
//        auto r = foo(std::ref(d1));

        std::future<std::string> r1 = std::async(std::launch::async, &foo, std::ref(d1));
//        std::this_thread::sleep_for(std::chrono::seconds(2));
//        std::cout << "we wait exception..." << std::endl;
        std:: cout <<  r1.get() << std::endl;

        auto r2 = std::async(std::launch::deferred, &foo, std::ref(d1));
        std:: cout  << r2.get() << std::endl;

    } catch (std::invalid_argument &ex) {
        std::cerr << "oops!" << std::endl;
    } catch (...) {
        std::cerr << "oops!" << std::endl;
    }
}


int main() {
    example_thread();
//    example_async();
}