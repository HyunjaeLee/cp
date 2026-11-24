#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> g(N);
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> color(N);
    auto bad = [&](int u) {
        auto cnt = 0;
        for (auto v : g[u]) {
            if (color[u] == color[v]) {
                cnt++;
            }
        }
        return 1 < cnt;
    };
    auto relax = [&](int u) {
        array<int, 3> cnt{};
        for (auto v : g[u]) {
            cnt[color[v]]++;
        }
        for (auto i = 0; i < 3; ++i) {
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
        for (auto v : g[u]) {
            if (bad(v)) {
                q.push(v);
            }
        }
    }
    for (auto i = 0; i < N; ++i) {
        cout << color[i] + 1 << " ";
    }
}
