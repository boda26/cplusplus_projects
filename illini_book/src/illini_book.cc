#include "illini_book.hpp"
#include <fstream>
#include <set>
#include <queue>

using namespace std;

// Your code here!
IlliniBook::IlliniBook(const string &people_fpath, const string &relations_fpath) {
    // read first file
    ifstream ifs1{people_fpath};
    for(std::string line; getline(ifs1, line); line = "") {
        int node = stoi(line);
        graph_.insert(make_pair(node, list<pair<int,string>>()));
    }
    // read second file
    ifstream ifs2{relations_fpath};
    for(std::string line; getline(ifs2, line); line = "") {
        vector<string> v;
        string temp;
        for (auto a: line) {
            if (a == ',') {
                v.push_back(temp);
                //cout << temp << endl;
                temp = "";
            } else {
                temp += a;
            }
        }
        v.push_back(temp);
        //cout << temp << endl;
        int first = stoi(v[0]);
        int second = stoi(v[1]);
        string path = v[2];
        graph_.at(first).push_back(make_pair(second,path));
        graph_.at(second).push_back(make_pair(first,path));
    }
}

list<int> IlliniBook::BFS(int start) const {
    list<int> bfs;
    queue<int> queue;
    set<int> set;
    queue.push(start);
    set.insert(start);
    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        bfs.push_back(vertex);
        for (auto it = graph_.at(vertex).begin(); it != graph_.at(vertex).end(); ++it) {
            int v = (*it).first;
            if (set.find(v) == set.end()) {
                queue.push(v);
                set.insert(v);
            }
        }
    }
    return bfs;
}

std::list<int> IlliniBook::BFS(int start, const std::string& relationship) const {
    list<int> bfs;
    queue<int> queue;
    set<int> set;
    queue.push(start);
    set.insert(start);
    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        bfs.push_back(vertex);
        for (auto it = graph_.at(vertex).begin(); it != graph_.at(vertex).end(); ++it) {
            int v = (*it).first;
            string r = (*it).second;
            if (set.find(v) == set.end() && r == relationship) {
                queue.push(v);
                set.insert(v);
            }
        }
    }
    return bfs;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    list<int> bfs = BFS(uin_1);
    for (auto it = bfs.begin(); it != bfs.end(); ++it) {
        if (*it == uin_2) {
            return true;
        }
    }
    return false;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    list<int> bfs = BFS(uin_1, relationship);
    if (bfs.empty()) {
        return false;
    }
    for (auto it = bfs.begin(); it != bfs.end(); ++it) {
        if (*it == uin_2) {
            return true;
        }
    }
    return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    queue<int> queue;
    map<int,int> dist;
    set<int> visited;
    for (const auto& a: graph_) {
        dist.insert(make_pair(a.first, -1));
    }
    queue.push(uin_1);
    dist.at(uin_1) = 0;
    visited.insert(uin_1);
    while(!queue.empty()) {
        int front = queue.front();
        queue.pop();
        for (auto it = graph_.at(front).begin(); it != graph_.at(front).end(); ++it) {
            int vertex = (*it).first;
            if (visited.find(vertex) == visited.end()) {
                visited.insert(vertex);
                dist.at(vertex) = dist.at(front) + 1;
                queue.push(vertex);
                if (vertex == uin_2) {
                    return dist.at(uin_2);
                }
            }
        }
    }
    return dist.at(uin_2);
}

int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    queue<int> queue;
    map<int,int> dist;
    set<int> visited;
    for (const auto& a: graph_) {
        dist.insert(make_pair(a.first, -1));
    }
    queue.push(uin_1);
    dist.at(uin_1) = 0;
    visited.insert(uin_1);
    while(!queue.empty()) {
        int front = queue.front();
        queue.pop();
        for (auto it = graph_.at(front).begin(); it != graph_.at(front).end(); ++it) {
            int vertex = (*it).first;
            if (visited.find(vertex) == visited.end() && (*it).second == relationship) {
                visited.insert(vertex);
                dist.at(vertex) = dist.at(front) + 1;
                queue.push(vertex);
                if (vertex == uin_2) {
                    return dist.at(uin_2);
                }
            }
        }
    }
    return dist.at(uin_2);
}

vector<int> IlliniBook::GetSteps(int uin, int n) const {
    vector<int> steps;
    queue<int> queue;
    map<int,int> dist;
    set<int> visited;
    for (const auto& a: graph_) {
        dist.insert(make_pair(a.first, -1));
    }
    queue.push(uin);
    dist.at(uin) = 0;
    visited.insert(uin);
    while(!queue.empty()) {
        int front = queue.front();
        queue.pop();
        for (auto it = graph_.at(front).begin(); it != graph_.at(front).end(); ++it) {
            int vertex = (*it).first;
            if (visited.find(vertex) == visited.end()) {
                visited.insert(vertex);
                dist.at(vertex) = dist.at(front) + 1;
                queue.push(vertex);
            }
        }
    }
    for (const auto& d: dist) {
        if (d.second == n) {
            steps.push_back(d.first);
        }
    }
    return steps;
}

size_t IlliniBook::CountGroups() const {
    size_t count = 0;
    set<int> set;
    queue<int> queue;
    for (auto const& a: graph_) {
        int vertex = a.first;
        if (set.find(vertex) == set.end()) {
            list<int> bfs = BFS(vertex);
            for (auto it = bfs.begin(); it != bfs.end(); ++it) {
                if (set.find(*it) == set.end()) {
                    set.insert(*it);
                }
            }
            count++;
        }
    }
    return count;
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
    size_t count = 0;
    set<int> set;
    queue<int> queue;
    for (auto const& a: graph_) {
        int vertex = a.first;
        if (set.find(vertex) == set.end()) {
            list<int> bfs = BFS(vertex, relationship);
            for (auto it = bfs.begin(); it != bfs.end(); ++it) {
                if (set.find(*it) == set.end()) {
                    set.insert(*it);
                }
            }
            count++;
        }
    }
    return count;
}

size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    size_t count = 0;
    set<int> set;
    queue<int> queue;
    for (auto const& a: graph_) {
        int vertex = a.first;
        if (set.find(vertex) == set.end()) {
            list<int> bfs = BFS(vertex, relationships);
            for (auto it = bfs.begin(); it != bfs.end(); ++it) {
                if (set.find(*it) == set.end()) {
                    set.insert(*it);
                }
            }
            count++;
        }
    }
    return count;
}

std::list<int> IlliniBook::BFS(int start, const std::vector<std::string> &relationships) const {
    list<int> bfs;
    queue<int> queue;
    set<int> set;
    queue.push(start);
    set.insert(start);
    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        bfs.push_back(vertex);
        for (auto it = graph_.at(vertex).begin(); it != graph_.at(vertex).end(); ++it) {
            int v = (*it).first;
            string r = (*it).second;
            if (set.find(v) == set.end()) {
                for (auto it2 = relationships.begin(); it2 != relationships.end(); ++it2) {
                    if (*it2 == r) {
                        queue.push(v);
                        set.insert(v);
                        break;
                    }
                }
            }
        }
    }
    return bfs;
}