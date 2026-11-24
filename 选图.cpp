#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int K, N, D, M;
    cin >> K >> N >> D >> M;
    vector<vector<int>> g(K * N);
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> color(K * N);
    auto bad = [&](int u) {
        auto cnt = 0;
        for (auto v : g[u]) {
            if (color[u] == color[v]) {
                cnt++;
            }
        }
        return D - 1 < cnt;
    };
    auto relax = [&](int u) {
        vector<int> cnt(K);
        for (auto v : g[u]) {
            cnt[color[v]]++;
        }
        for (auto i = 0; i < K; ++i) {
            if (cnt[i] <= D - 1) {
                color[u] = i;
                break;
            }
        }
    };
    queue<int> q;
    for (auto i = 0; i < K * N; ++i) {
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
    vector<vector<int>> F(K);
    for (auto i = 0; i < K * N; ++i) {
        F[color[i]].push_back(i);
    }
    for (const auto &f : F) {
        if (ssize(f) < N)
            continue;
        for (auto i = 0; i < N; ++i) {
            cout << f[i] + 1 << " ";
        }
        break;
    }
}
