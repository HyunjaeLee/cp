#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N);
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> color(N);
    auto bad = [&](int u) {
        array<int, 2> cnt{};
        for (auto v : adj[u]) {
            cnt[color[v]]++;
        }
        return 2 <= cnt[color[u]];
    };
    auto relax = [&](int u) {
        array<int, 2> cnt{};
        for (auto v : adj[u]) {
            cnt[color[v]]++;
        }
        for (auto i = 0; i < 2; ++i) {
            if (cnt[i] <= 1) {
                color[u] = i;
                break;
            }
        }
    };
    queue<int> q;
    for (auto i = 0; i < N; ++i) {
        if (bad(i)) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        if (!bad(u))
            continue;
        relax(u);
        for (auto v : adj[u]) {
            if (bad(v)) {
                q.push(v);
            }
        }
    }
    for (auto x : color) {
        cout << x;
    }
}
