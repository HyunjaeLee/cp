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

#include <atcoder/modint>

#ifndef BIPARTITE_COLORING_HPP
#define BIPARTITE_COLORING_HPP

#include <optional>
#include <queue>
#include <vector>

std::optional<std::vector<int>> bipartite_coloring(const std::vector<std::vector<int>> &g) {
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
            for (auto v : g[u]) {
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

#include <atcoder/dsu>

#define TC
void solve() {
    int N;
    cin >> N;
    vector<vector<int>> A(2 * N, vector<int>(N));
    for (auto &a : A) {
        read(a);
    }
    auto Conflict = [&](int i, int j) {
        for (auto k = 0; k < N; ++k) {
            if (A[i][k] == A[j][k]) {
                return true;
            }
        }
        return false;
    };
    vector<int> used(2 * N);
    vector<int> ans;
    while (true) {
        auto p = -1;
        for (auto j = 0; j < N; ++j) {
            vector<int> freq(N + 1);
            for (auto i = 0; i < 2 * N; ++i) {
                if (used[i]) {
                    continue;
                }
                ++freq[A[i][j]];
            }
            for (auto i = 0; i < 2 * N; ++i) {
                if (used[i]) {
                    continue;
                }
                if (freq[A[i][j]] == 1) {
                    p = i;
                    break;
                }
            }
            if (p != -1) {
                break;
            }
        }
        if (p == -1) {
            break;
        }
        used[p] = true;
        ans.push_back(p);
        for (auto i = 0; i < 2 * N; ++i) {
            if (used[i]) {
                continue;
            }
            if (Conflict(p, i)) {
                used[i] = true;
            }
        }
    }
    vector<vector<int>> adj(2 * N);
    atcoder::dsu dsu(2 * N);
    for (auto i = 0; i < 2 * N; ++i) {
        if (used[i]) {
            continue;
        }
        for (auto j = i + 1; j < 2 * N; ++j) {
            if (used[j]) {
                continue;
            }
            if (Conflict(i, j)) {
                dsu.merge(i, j);
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    using Z = atcoder::modint998244353;
    Z cnt = 1;
    for (auto i = 0; i < 2 * N; ++i) {
        if (used[i]) {
            continue;
        }
        if (dsu.leader(i) == i) {
            cnt *= 2;
        }
    }
    cout << cnt.val() << "\n";
    auto color = *bipartite_coloring(adj);
    for (auto i = 0; i < 2 * N; ++i) {
        if (!used[i] && color[i]) {
            ans.push_back(i);
        }
    }
    assert(ssize(ans) == N);
    show<1>(ans);
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
