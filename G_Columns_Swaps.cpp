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

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    read<1>(A);
    read<1>(B);
    vector<vector<int>> F(N);
    for (auto i = 0; i < N; ++i) {
        F[A[i]].push_back(i);
        F[B[i]].push_back(i + N);
    }
    for (auto i = 0; i < N; ++i) {
        if (size(F[i]) != 2) {
            cout << "-1\n";
            return;
        }
    }
    vector<vector<int>> G(2 * N);
    for (auto i = 0; i < N; ++i) {
        auto u = i, v = i + N;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (auto i = 0; i < N; ++i) {
        auto u = F[i][0], v = F[i][1];
        G[u].push_back(v);
        G[v].push_back(u);
    }
    auto opt = bipartite_coloring(G);
    if (!opt) {
        cout << "-1\n";
        return;
    }
    auto color = std::move(*opt);
    vector<int> cid(2 * N, -1);
    auto timer = 0;
    for (auto i = 0; i < 2 * N; ++i) {
        if (cid[i] != -1)
            continue;
        [&](this auto &&self, int u) -> void {
            cid[u] = timer;
            for (auto v : G[u]) {
                if (cid[v] == -1) {
                    self(v);
                }
            }
        }(i);
        timer++;
    }
    vector<vector<int>> C(timer);
    for (auto i = 0; i < 2 * N; ++i) {
        C[cid[i]].push_back(i);
    }
    vector<int> ans;
    for (const auto &comp : C) {
        array<vector<int>, 2> P;
        for (auto x : comp) {
            if (x < N) {
                P[color[x]].push_back(x);
            }
        }
        if (P[0].size() > P[1].size())
            swap(P[0], P[1]);
        ans.insert(ans.end(), P[0].begin(), P[0].end());
    }
    cout << ans.size() << "\n";
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
