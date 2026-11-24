#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;

// clang-format off
using i8 = signed char; using u8 = unsigned char;
using i32 = int;        using u32 = unsigned;
using i64 = long long;  using u64 = unsigned long long;
using i128 = __int128;  using u128 = unsigned __int128;
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <int I = 0> void read(auto &a) { for (auto &x : a) { cin >> x; if constexpr (I) { x -= I; } } }
template <int I = 0> void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) { if (it != a.begin()) { cout << sep; }
    auto x = *it; if constexpr (I) { x += I; } cout << x; } cout << end;
}
// clang-format on

#ifndef BIPARTITE_COLORING_HPP
#define BIPARTITE_COLORING_HPP

#include <optional>
#include <queue>
#include <vector>

std::optional<std::vector<int>> bipartite_coloring(const std::vector<std::vector<int>> &g) {
    auto n = int(g.size());
    std::vector<int> color(n, -1);
    vector<int> parent(n);
    for (auto i = 0; i < n; ++i) {
        if (color[i] != -1) {
            continue;
        }
        std::queue<int> q;
        q.push(i);
        color[i] = 0;
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (color[v] == -1) {
                    q.push(v);
                    color[v] = color[u] ^ 1;
                } else if (color[v] == color[u]) {
                }
            }
        }
    }
    return color;
}

#endif // BIPARTITE_COLORING_HPP

#define TC
void solve() {
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
    vector<int> parent(N, -1);
    vector<int> color(N, -1);
    color[0] = 0;
    auto c = -1, p = -1;
    [&](this auto &&self, int u) -> void {
        for (auto v : adj[u]) {
            if (color[v] == -1) {
                parent[v] = u;
                color[v] = color[u] ^ 1;
                self(v);
            } else if (color[u] == color[v] && c == -1) {
                c = u, p = v;
            }
        }
    }(0);
    if (c == -1) {
        cout << "-1\n";
        return;
    }
    vector<int> path;
    for (auto x = c; x != p; x = parent[x]) {
        path.push_back(x);
    }
    path.push_back(p);
    cout << path.size() << "\n";
    show<1>(path);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
