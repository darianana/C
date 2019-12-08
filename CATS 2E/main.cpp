#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;
using ObjectId = unsigned long long int;

struct GameObject
{
    ObjectId id;
    std::string name;
    size_t x;
    size_t y;
};

bool operator>(const GameObject& a, const GameObject& b) { return a.id > b.id; }

template <class Tp, template <class> class Compare>
class DereferenceCompare {
    Compare<Tp> comp;

public:
    bool operator()(const Tp* const a, const Tp* const b) const {
        return comp(*a, *b);
    }
};

class GameDatabase {
public:
    GameDatabase() = default;

    void Insert(ObjectId id, std::string name, size_t x, size_t y) {
        Remove(id);
        access_id[id] = {id, name, x, y};
        access_pos[std::make_pair(x, y)].insert(&access_id[id]);
        access_name[name].insert(&access_id[id]);
    }

    void Remove(ObjectId id) {
        if (access_id.find(id) != access_id.end()) {
            access_pos[std::make_pair(access_id[id].x, access_id[id].y)].erase(&access_id[id]);
            access_name[access_id[id].name].erase(&access_id[id]);
            access_id.erase(id);
        }
    }

    std::vector<GameObject> DataByName(std::string name) const {
        std::vector<GameObject> answ;
        if (access_name.find(name) != access_name.end()) {
            for (auto i : (*access_name.find(name)).second) {
                answ.push_back(*i);
            }
        }
        return answ;
    }

    std::vector<GameObject> DataByPosition(size_t x, size_t y) const {
        std::vector<GameObject> answ;
        if (access_pos.find(std::make_pair(x, y)) != access_pos.end()) {
            for (auto i : (*access_pos.find(std::make_pair(x, y))).second) {
                answ.push_back(*i);
            }
        }
        return answ;
    }

    std::vector<GameObject> Data() const {
        std::vector<GameObject> answ;
        for (auto i : access_id) {
            answ.push_back(i.second);
        }
        return answ;
    }

private:
    std::map<ObjectId, GameObject, std::greater<ObjectId>> access_id;

    std::map<std::pair<size_t, size_t>,
            std::set<GameObject*, DereferenceCompare<GameObject, std::greater>>>
            access_pos;

    std::unordered_map<
            std::string,
            std::set<GameObject*, DereferenceCompare<GameObject, std::greater>>>
            access_name;
};
template<class Stream>
void operator<<(Stream& s, const GameObject& obj)
{
    s << obj.id << ' ' << obj.name << ' ' << obj.x << ' ' << obj.y << '\n';
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    GameDatabase db;
    // *******************************
    size_t n;
    cin >> n;
    for (size_t i = 0; i < n; ++i)
    {
        size_t op_type, id, x, y;
        string name;
        cin >> op_type >> id;
        if (op_type) // remove operation
        {
            db.Remove(id);
            continue;
        }
        cin.ignore(1);
        cin >> name >> x >> y;
        db.Insert(id, std::move(name), x, y);
    }
    // *******************************
    for (size_t i = 0; i <= 49; ++i)
        for (size_t j = 0; j <= 49; ++j)
            for (const auto& e : db.DataByPosition(i, j))
                cout << e;
    for (char i = 'a'; i <= 'z'; ++i)
        for (char j = 'a'; j <= 'z'; ++j)
            for (const auto& e : db.DataByName(string() + i + j))
                cout << e;
    for (const auto& e : db.Data())
        cout << e;
    cout.flush();
    return 0;
}