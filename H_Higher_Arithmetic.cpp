#include <bits/stdc++.h>
using namespace std;

struct DSU {
    explicit DSU(int n) : parent_or_size(n, -1) {}
    int leader(int a) { return parent_or_size[a] < 0 ? a : parent_or_size[a] = leader(parent_or_size[a]); }
    int merge(int a, int b) {
        a = leader(a);
        b = leader(b);
        if (a == b) {
            return a;
        }
        if (-parent_or_size[a] < -parent_or_size[b]) {
            swap(a, b);
        }
        parent_or_size[a] += parent_or_size[b];
        parent_or_size[b] = a;
        return a;
    }
    vector<int> parent_or_size;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto &x : A)
        cin >> x;
    deque<pair<int, int>> dq;
    for (auto i = 0; i < N; ++i) {
        if (A[i] == 1) {
            dq.emplace_back(A[i], i);
        }
    }
    for (auto i = 0; i < N; ++i) {
        if (A[i] == 2) {
            dq.emplace_back(A[i], i);
        }
    }
    DSU dsu(N);
    while (2 <= dq.size() && dq.front().first == 1) {
        auto [x, i] = dq.front();
        dq.pop_front();
        auto [y, j] = dq.back();
        dq.pop_back();
        auto l = dsu.merge(i, j);
        if (x + y < 3) {
            dq.emplace_back(x + y, l);
        }
    }
    {
        vector<vector<int>> G(N);
        for (auto i = 0; i < N; ++i) {
            G[dsu.leader(i)].push_back(A[i]);
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        for (auto i = 0; i < N; ++i) {
            if (G[i].empty())
                continue;
            auto sum = 0;
            for (auto x : G[i]) {
                sum += x;
            }
            pq.emplace(sum, i);
        }
        while (2 <= pq.size() && pq.top().first == 1) {
            auto [x, i] = pq.top();
            pq.pop();
            auto [y, j] = pq.top();
            pq.pop();
            auto l = dsu.merge(i, j);
            pq.emplace(x + y, l);
        }
    }
    vector<vector<int>> G(N);
    for (auto i = 0; i < N; ++i) {
        G[dsu.leader(i)].push_back(A[i]);
    }
    auto start = false;
    for (auto i = 0; i < N; ++i) {
        if (G[i].empty())
            continue;
        if (start) {
            cout << "*";
        }
        start = true;
        cout << "(";
        for (auto j = 0; j < int(G[i].size()); ++j) {
            if (j) {
                cout << "+";
            }
            cout << G[i][j];
        }
        cout << ")";
    }
}
