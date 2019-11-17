#include <cassert>
#include <iostream>
#include <vector>
#include <functional>

//#include "num.h"
//#include "num.cpp"

using namespace std;

class Num {
public:
    Num(int value=0, int modulo=0);
    Num(const Num& other);

    int value;
    int modulo;
};
Num::Num(int value, int modulo) {
    this->value = value % modulo;
    this->modulo = modulo;
}

Num::Num(const Num& other) {
    this->modulo = 0;
    this->value = other.value;
}

int main() {
    {
        Num a(1, 10);
        assert(a.value == 1);
        assert(a.modulo == 10);

        Num b(2001, 10);
        assert(b.value == 1);
        assert(b.modulo == 10);
    }

    {
        Num a(20000, 100);
        assert(a.value == 0);
        assert(a.modulo == 100);

        Num b = a;
        assert(b.value == 0);
        assert(b.modulo == 0);
    }

    {
        Num a(99, 100);
        assert(a.value == 99);
        assert(a.modulo == 100);

        Num b = a;
        assert(b.value == 99);
        assert(b.modulo == 0);
    }
    cout << 1 << endl;
}