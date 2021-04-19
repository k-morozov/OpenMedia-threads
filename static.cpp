//
// Created by focus on 06.04.2021.
//

#include <string>

void foo() {
    static std::string hw {"Hello world"};
};

bool bar_hw_guard; // = 0, = false
std::string bar_hw; // no ctor !!! allocate

void bar_old() {
    if (!bar_hw_guard) {
        bar_hw = "Hello World!"; // ctor
        bar_hw_guard = true;
    }
};

int main() {
    foo();
    foo();

    bar_old();
    bar_old();
}