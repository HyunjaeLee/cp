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

#ifndef TREE_DIAMETER_HPP
#define TREE_DIAMETER_HPP

#include <algorithm>
#include <cassert>
#include <vector>

// return (diameter, path)
// centers are path[d / 2] and path[(d + 1) / 2]
auto tree_diameter(const auto &g) {
    assert(0 < g.size());
    auto n = int(g.size());
    std::vector<int> parent(n, -1);
    std::vector<int> depth(n);
    auto dfs = [&](int x) {
        std::vector<int> st;
        st.push_back(x);
        parent[x] = -1;
        depth[x] = 0;
        while (!st.empty()) {
            auto u = st.back();
            st.pop_back();
            for (auto v : g[u]) {
                if (v != parent[u]) {
                    st.push_back(v);
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                }
            }
        }
        auto it = std::ranges::max_element(depth);
        auto r = int(it - depth.begin());
        return std::pair(r, *it);
    };
    auto x = dfs(0).first;
    auto [y, d] = dfs(x);
    std::vector<int> path;
    for (auto u = y; ~u; u = parent[u]) {
        path.push_back(u);
    }
    return std::pair(d, path);
}

#endif // TREE_DIAMETER_HPP

void solve() {
    int N;
    cin >> N;
    vector<vector<int>> g(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> color(N);
    read<1>(color);
    auto [d, path] = tree_diameter(g);
    if (d % 2 == 0) {
        auto c = path[d / 2];
        vector<int> depth(N);
        [&](this auto &&self, int u, int p) -> void {
            for (auto v : g[u]) {
                if (v == p)
                    continue;
                depth[v] = depth[u] + 1;
                self(v, u);
            }
        }(c, c);
        i64 ans = 0;
        vector<int> f(N);
        for (auto v : g[c]) {
            [&](this auto &&self, int u, int p) -> void {
                if (depth[u] == d / 2) {
                    ans += f[color[u]];
                }
                for (auto v : g[u]) {
                    if (v == p)
                        continue;
                    self(v, u);
                }
            }(v, c);
            [&](this auto &&self, int u, int p) -> void {
                if (depth[u] == d / 2) {
                    f[color[u]]++;
                }
                for (auto v : g[u]) {
                    if (v == p)
                        continue;
                    self(v, u);
                }
            }(v, c);
        }
        cout << ans << "\n";
    } else {
        auto c1 = path[d / 2];
        auto c2 = path[(d + 1) / 2];
        vector<int> d1(N, -1);
        d1[c1] = 0;
        [&](this auto &&self, int u, int p) -> void {
            for (auto v : g[u]) {
                if (v == p)
                    continue;
                d1[v] = d1[u] + 1;
                self(v, u);
            }
        }(c1, c2);
        vector<int> d2(N, -1);
        d2[c2] = 0;
        [&](this auto &&self, int u, int p) -> void {
            for (auto v : g[u]) {
                if (v == p)
                    continue;
                d2[v] = d2[u] + 1;
                self(v, u);
            }
        }(c2, c1);
        vector<int> f1(N);
        for (auto i = 0; i < N; ++i) {
            if (d1[i] == d / 2) {
                f1[color[i]]++;
            }
        }
        vector<int> f2(N);
        for (auto i = 0; i < N; ++i) {
            if (d2[i] == d / 2) {
                f2[color[i]]++;
            }
        }
        i64 ans = 0;
        for (auto i = 0; i < N; ++i) {
            ans += i64(f1[i]) * (f2[i]);
        }
        cout << ans << "\n";
    }
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
