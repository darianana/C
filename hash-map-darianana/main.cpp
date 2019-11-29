#include <iostream>
#include "hash_map.hpp"
#include <unordered_map>
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <deque>

#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <tuple>
#include <type_traits>
#include <functional>
#include <utility>
#include <atomic>
#include <thread>
#include <future>
#include <chrono>
#include <iterator>
#include <memory>


template<typename T>
struct allocator_t : fefu::allocator<T>{
public:
    std::string m = "message";
};

template<typename IT>
bool compare_it(IT it, std::pair<int,int> pair){
    return (it.operator*().first == pair.first && it.operator*().second == pair.second);
}
template<typename TimePoint>
class time_meter
{
public:
    using time_point = TimePoint;

private:
    std::function<time_point()> m_fnow;
    std::function<double(time_point, time_point)> m_fsec;
    time_point m_begin;
    time_point m_stop;
    bool m_stopped;

public:
    template<typename FNow, typename FSec>
    time_meter(FNow&& now, FSec&& sec) : m_fnow(std::forward<FNow>(now)), m_fsec(std::forward<FSec>(sec)), m_begin(m_fnow()), m_stopped(false) { }

    double seconds() const
    {
        if (m_stopped)
            return m_fsec(m_begin, m_stop);
        return m_fsec(m_begin, m_fnow());
    }

    void restart()
    {
        m_stopped = false;
        m_begin = m_fnow();
    }

    void stop()
    {
        if (m_stopped)
            return;
        m_stop = m_fnow();
        m_stopped = true;
    }

    void start()
    {
        if (!m_stopped)
            return;
        m_stopped = false;
        m_begin += m_fnow() - m_stop;
    }
};
auto create_tm()
{
    using tm_type = time_meter<std::chrono::high_resolution_clock::time_point>;

    static const auto get_sec = [](tm_type::time_point p1, tm_type::time_point p2)
    {
        return static_cast<double>((p2 - p1).count()) / std::chrono::high_resolution_clock::period::den;
    };

    return tm_type(std::chrono::high_resolution_clock::now, get_sec);
}

using namespace std;

struct custom_hash
{
    vector<long long unsigned int> rnd;

    custom_hash()
    {
        for (int i = 0; i < 1000000; ++i)
            rnd.push_back(rand());
    }

    long long unsigned int operator()(int i) const
    {
        return rnd[i];
    }
};

int main() {

    std::initializer_list<std::pair<int,int>> i_list   {{1,1}, {2,2}, {3, 3}};
    std::vector<std::pair<int,int>> range = i_list;
    std::vector<std::pair<const int, int>> test_vec;
    for (int i = 0; i < 1000; ++i) {
        test_vec.emplace_back(i, i);
    }

    {
        fefu::hash_map<int, int> a(10);
        assert(a.size() == 10);
        fefu::hash_map<int, int, std::hash<int>, std::equal_to<int>, allocator_t<std::pair<const int, int>>> a_1(10);
        fefu::hash_map<int, int> b(range.begin(), range.end(), 10);
        fefu::hash_map<int, int> d (a);
        fefu::hash_map<int, int> e (std::move(a));
        auto all = allocator_t<std::pair<const int, int>>();
        fefu::hash_map<int, int, std::hash<int>, std::equal_to<int>, allocator_t<std::pair<const int, int>>> f (all);
        fefu::hash_map<int, int, std::hash<int>, std::equal_to<int>, allocator_t<std::pair<const int, int>>> g (f, all);
        fefu::hash_map<int, int, std::hash<int>, std::equal_to<int>, allocator_t<std::pair<const int, int>>> h (std::move(a_1), all);
        assert(b.begin() != b.end());
        for(auto x : i_list){
            assert(b.find(x.first) != b.end());
        }
        assert(d.size() == 10);
        assert(e.size() == 10);
        assert(f.get_allocator().m == "message");
        assert(g.get_allocator().m == "message" && g.empty());
        assert(h.get_allocator().m == "message" && h.size() == 10);
        fefu::hash_map<int, int> assig = b;
        auto begin = b.begin();
        for(auto i: assig){
            assert(i.first == begin.operator*().first);
            ++begin;
        }
        fefu::hash_map<int, int> assig_m = std::move(assig);
        auto begin_m = b.begin();
        for(auto i: assig_m){
            assert(i.first == begin_m.operator*().first);
            ++begin_m;
        }
        fefu::hash_map<int, int> c_1 = {{1,1}, {2,2}, {3, 3}};
        for(auto x : i_list){
            assert(c_1.find(x.first) != b.end());
        }
        assert(c_1.bucket_count() == 3);
        fefu::hash_map<int, int> hash_map;
        hash_map = b;
        auto hh = hash_map.begin();
        for(auto x: b){
            assert(x.first == hh.operator*().first);
            ++hh;
        }
        std::cout << "Constructors-operator= test passed" << std::endl;
    }

    {
        fefu::hash_map<int, int> map;
        map.insert(range[0]);
        fefu::hash_map_const_iterator<std::pair<const int, int>> it = map.begin();
        assert(compare_it(it, range[0]));
        auto it1 (map.cbegin());
        map.begin()++;
        assert(compare_it(it1, range[0]));
        const auto it2 = map.end();
        assert(it2 != it);
        auto it3 = map.cend();
        assert(it3 == it2);
        assert(it.operator++()== it2);
        assert(it1.operator++() == it);
        std::cout << "Iterators test passed"<< std::endl;
        it1++;
    }

    {
        fefu::hash_map<int, int> hash_map(test_vec.begin(), test_vec.end());
        auto it = hash_map.begin();
        hash_map.erase(it);
        assert(hash_map.find(it->first) == hash_map.end());
        auto it1 = hash_map.cbegin();
        hash_map.erase(it1);
        assert(hash_map.find(it1->first) == hash_map.end());
        hash_map.erase(10);
        assert(hash_map.find(10) == hash_map.end());
        hash_map.erase(hash_map.begin(), hash_map.end());
        assert(!hash_map.empty());
        fefu::hash_map<int, int> hash_map1(test_vec.begin(), test_vec.end());
        hash_map1.clear();
        assert(hash_map1.empty());
        assert(!hash_map1.erase(-4));
        assert(hash_map1.erase(hash_map1.end()) == hash_map1.end());
        assert(hash_map1.erase(hash_map1.cend()) == hash_map1.cend());
        std::cout << "Erase test passed"<< std::endl;

    }

    {
        fefu::hash_map <int, int> map1 (range.begin(), range.end());
        fefu::hash_map <int, int> map3 (range.begin(), range.end());
        map1.hash_function();
        map1.key_eq();
        fefu::hash_map <int, int> map2 (6);
        for (int kI = 4; kI <=6; ++kI) {
            map2.emplace(kI, kI);
            map3.emplace(kI, kI);
        }
        map1.merge(map2);
        assert(map3 == map1);
        std::cout << "Merge test passed!"<< std::endl;
    }

//
    {
        fefu::hash_map <int, int> map1;
        map1.reserve(10);
        auto it = map1.emplace(4,4);
        map1.emplace(5,6);
        map1.emplace(3, 2);
        map1.emplace(6,7);
        assert(it.first->first == 4);

        std::cout << "Reserve test passed!"<< std::endl;

    }
//
    std::cout << "All tests passed!"<< std::endl;

    {
        using namespace fefu;
        auto tm = create_tm();
        hash_map<int, int, custom_hash> m(1000000);
        m.max_load_factor(0.1f);
        for (int i = 0; i < 1000000; ++i)
        {
            cout << i << endl;
            m.insert({i, i * 3});
        }
        for (int i = 100; i < 999999; ++i)
        {
            cout << i << endl;
            m.erase(i);
        }
        for (int i = 0; i < 1000000; ++i)
        {
            m.insert({i, i * 3});
        }
        for (int i = 0; i < 1000000; ++i)
        {
            m.insert({i, i * 3});
        }
        for (int i = 100; i < 999999; ++i)
        {
            m.erase(i);
        }
        for (int i = 100; i < 999999; ++i)
        {
            m.erase(i);
        }
        if (m.size() != 101)
            cout << "INVALID SIZE" << endl;
        for (int i = 0; i < 1000; ++i)
            m.insert({rand() % 1000000, rand()});
        cout << "**********\n" << "STRESS TIME = " << tm.seconds() << "\n**********" << endl;
    }

    return 0;
}