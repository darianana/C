#include "num.h"
    Num::Num(int value, int modulo) {
        this->value = value % modulo;
        this->modulo = modulo;
    }

    Num::Num(const Num& other) {
        this->modulo = 0;
        this->value = other.value;
}