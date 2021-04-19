//
// Created by focus on 19.04.2021.
//

#include <iostream>
#include <string>
#include <mutex>

class some_data {
    int a;
    std::string b;

public:
    void do_something() {
        std::cout << "my protected message" << std::endl;
    }
};

class data_wrapper {
private:
    some_data data;
    std::mutex m;

public:
    template<class Funtion>
    void proccess_data(Funtion func) {
        std::lock_guard<std::mutex> lock(m);
        func(data);
    }
};

// ***************************************************
some_data *ptr;
void crack(some_data & protected_data) {
    ptr = &protected_data;
}
// ***************************************************
int main() {
    data_wrapper wrapper;
    wrapper.proccess_data(crack);
    ptr->do_something();
}