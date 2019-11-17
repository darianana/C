#include <iostream>
#include "hash_map.hpp"

int main() {
    fefu::hash_map<int, int> h(10);
    int a = 10;
    h[a] = 5;
    return 0;
}