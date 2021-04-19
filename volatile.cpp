//
// Created by focus on 06.04.2021.
//

int main() {
    volatile
    int a;

    a = 100;
    a = 42;
    a = 42;

    return a;
}