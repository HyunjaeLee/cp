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

std::optional<std::vector<int>> bipartite_coloring(const auto &g) {
    auto n = int(g.size());
    std::vector<int> color(n, -1);
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
            for (auto [v, w] : g[u]) {
                if (color[v] == -1) {
                    q.push(v);
                    color[v] = color[u] ^ 1;
                } else if (color[v] == color[u]) {
                    return std::nullopt;
                }
            }
        }
    }
    return color;
}

#endif // BIPARTITE_COLORING_HPP

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> adj(N);
    for (auto i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    for (auto i = 0; i < N; ++i) {
        ranges::sort(adj[i], {}, [&](auto p) { return p.second; });
    }
    auto pred = [&](i64 x) {
        vector<vector<pair<int, int>>> G(N);
        for (auto u = 0; u < N; ++u) {
            for (auto [v, w] : adj[u]) {
                if (w < x) {
                    G[u].emplace_back(v, w);
                }
            }
        }
        for (auto u = 0; u < N; ++u) {
            if (2 <= size(G[u])) {
                auto a = G[u][0].second;
                auto b = G[u][1].second;
                if (a + b < x) {
                    return false;
                }
            }
        }
        return bool(bipartite_coloring(G));
    };
    i64 L = 0, R = i64(3e9);
    auto ans = *ranges::partition_point(views::iota(L, R), pred) - 1;
    cout << ans << "\n";
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
