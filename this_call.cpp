//
// Created by focus on 19.04.2021.
//
#include <iostream>
#include <thread>


static void foo_global_static(int num) {
    std::cout << "Global->static->foo() " << num << std::endl;
}

void foo_global_simple(int num) {
    std::cout << "Global->simple->foo() " << num << std::endl;
}

struct Foo {
    void foo_simple(int num) {
        std::cout << "Foo:foo() simple: " << num << std::endl;
    }

    static void foo_static(int num) {
        std::cout << "Foo:foo() static: " << num << std::endl;
    }
};


int main() {
    std::thread th1(foo_global_static, 1);
    if (th1.joinable()) {
        th1.join();
    }

    std::thread th2(foo_global_simple, 2);
    if (th2.joinable()) {
        th2.join();
    }

    Foo foo;

    std::thread th3(&Foo::foo_simple, foo, 3);
    if (th3.joinable()) {
        th3.join();
    }

    std::thread th4(Foo::foo_static, 4);
    if (th4.joinable()) {
        th4.join();
    }

}
