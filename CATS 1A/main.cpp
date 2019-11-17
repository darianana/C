#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
#include <functional>
#include <set>
#include <queue>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include <cassert>

class PrimeNumberGenerator {
  public:
    int start_prime;
    explicit PrimeNumberGenerator(int start);
    int GetNextPrime();
};

PrimeNumberGenerator ::PrimeNumberGenerator(int start) {
        start_prime = start;
}
int PrimeNumberGenerator :: GetNextPrime() {
    int count = 0;
    for (int i = start_prime;; i++)
    {
        count = 0;
        for (int j = 2; j <= i; j++)
        {
            if (i % j == 0)
            {
                count++;
            }
        }
        if (count == 1)
        {
            start_prime = i + 1;
            return i;
        }
    }
}

int main() {
    int start, num;
    std::cin >> start >> num;
    PrimeNumberGenerator gen(start);
    for (int i = 0; i < num; ++i) {
        std::cout << gen.GetNextPrime() << " ";
    }
}