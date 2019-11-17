#include <cstdint>
#include "num.h"
Num :: Num(int value, int modulo){
    this->value = value % modulo;
    this->modulo = modulo;
}

Num &Num::operator=(const Num& other){
    modulo = other.modulo;
    value = other.value;
    return *this;
}

Num Num :: operator+(const Num& other){
    Num b (0, other.modulo);
    b.value = (static_cast<int64_t>(this->value) + other.value) % other.modulo;
    return b;
}

Num Num :: operator-(const Num& other){
    Num b(0, this->modulo);
    b.value = (static_cast<int64_t>(this->value) - other.value) % this->modulo;
    return b;
}

Num Num :: operator*(const Num& other){
    Num b (0, other.modulo);
    b.value = (static_cast<int64_t>(this->value) * other.value) % other.modulo;
    return b;
}

Num Num :: operator+(int num){
    value = (static_cast<int64_t>(this->value) + num) % this->modulo;
    return *this;
}

Num Num :: operator-(int num){
    value = (static_cast<int64_t>(this->value) - num) % this->modulo;
    return *this;
}

Num Num :: operator*(int num){
    value = (static_cast<int64_t>(this->value) * num) % this->modulo;
    return *this;
}

Num &Num :: operator+=(const Num& other){
    value = (static_cast<int64_t>(this->value) + other.value) % this->modulo;
    return *this;
}

Num &Num :: operator-=(const Num& other){
    value = (static_cast<int64_t>(this->value) - other.value) % this->modulo;
    if (value < 0)
        value = modulo + this->value;
    return *this;
}

Num &Num :: operator*=(const Num& other){
    value = (static_cast<int64_t>(this->value) * other.value) % this->modulo;
    return *this;
}

Num &Num :: operator+=(int num){
    value = (static_cast<int64_t>(this->value) + num) % this->modulo;
    return *this;
}

Num &Num :: operator-=(int num){
    value = (static_cast<int64_t>(this->value) - num) % this->modulo;
    if (value < 0)
        value = modulo + this->value;
    return *this;
}

Num &Num :: operator*=(int num){
    value = (static_cast<int64_t>(this->value) * num) % this->modulo;
    return *this;
}