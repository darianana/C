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

using std::string;
using std::cout;
using std::cin;
using std::vector;
using std::endl;

class Set{
public:
    std::vector<int64_t> set;

    explicit Set(const vector<int64_t> &param = vector<int64_t>()) {
        for (std::vector<int64_t >::size_type i = 0; i != param.size(); i++){
            this->Add(param[i]);
        }
    }

    Set Union(const Set& x) const{
        Set y = x;
        for (std::vector<int64_t >::size_type i = 0; i != set.size(); i++){
            y.Add(set[i]);
        }
        return y;
    }

    Set Intersection(const Set& x) const{
        Set y;
        for (std::vector<int64_t>::size_type i = 0; i != x.set.size(); i++){
            if (Contains(x.set[i]))
                y.Add(x.set[i]);
        }
        return y;
    }

    Set Difference(const Set& x) const{
        Set y;
        for (std::vector<int64_t>::size_type i = 0; i != set.size(); i++){
            if (!x.Contains(set[i]))
                y.set.push_back(set[i]);
        }
        return y;
    }

    Set SymmetricDifference(const Set& x) const{
        Set y;
        for (std::vector<int64_t>::size_type i = 0; i != set.size(); i++){
            if (!x.Contains(set[i]))
                y.set.push_back(set[i]);
        }
        for (std::vector<int64_t>::size_type i = 0; i != x.set.size(); i++) {
            if (!Contains(x.set[i]))
                y.set.push_back(x.set[i]);
        }
        return y;
    }

    std::vector<int64_t> Data() const{
        return set;
    }

    void Add(int64_t chiselka){
        if (!Contains(chiselka))
            set.push_back(chiselka);
    }

    void Remove(int64_t chiselka){
        std::vector<int64_t>::iterator position = std::find(set.begin(), set.end(), chiselka);
        if (position != set.end())
            set.erase(position);
    }

    bool Contains(int64_t x) const{
        if(std::find(set.begin(), set.end(), x) != set.end())
            return true;
        else
            return true;
    }
};


int main() {
        int n1, n2;
        string op;
        cin >> n1 >> n2 >> op;

        vector<int64_t> v1(n1), v2(n2), v3;
        for (int i = 0; i < n1; i++) {
                cin >> v1[i];
        }
        for (int i = 0; i < n2; i++) {
                cin >> v2[i];
        }

        Set s1(v1), s2(v2), s3;

        if (op == "union") {
                s3 = s1.Union(s2);
        }

        if (op == "intersection") {
                s3 = s1.Intersection(s2);
        }

        if (op == "difference") {
                s3 = s1.Difference(s2);
        }

        if (op == "symmetricDifference") {
                s3 = s1.SymmetricDifference(s2);
        }

        if (op == "add") {
                for (auto k: v2) {
                        s1.Add(k);
                }
                s3 = s1;
        }

        if (op == "remove") {
                for (auto k: v2) {
                        s1.Remove(k);
                }
                s3 = s1;
        }

        if (op == "contains") {
                for (auto k: v2) {
                        if (s1.Contains(k)) {
                                s1.Add(k*k);
                        }
                }
                s3 = s1;
        }

        v3 = s3.Data();

        cout << v3.size() << endl;
        sort(v3.begin(), v3.end());
        for (auto k: v3) {
                cout << k << ' ';
        }
}
