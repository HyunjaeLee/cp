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

#ifndef REROOTING_HPP
#define REROOTING_HPP

#include <ranges>
#include <vector>

/*
    vector<vector<pair<int, EdgeWeight>>> g;
    struct Subtree {};
    struct Child {};
    auto rake = [&](Child l, Child r) -> Child {};
    auto add_edge = [&](Subtree d, EdgeWeight w) -> Child {};
    auto add_vertex = [&](Child d, int i) -> Subtree {};
    auto e = []() -> Child {};
*/

auto rerooting(const auto &g, auto rake, auto add_edge, auto add_vertex, auto e) {
    auto n = int(g.size());
    using Child = decltype(e());
    using Subtree = decltype(add_vertex(e(), 0));
    std::vector<Subtree> dp(n), dp_parent(n);
    std::vector<int> bfs_order, parent(n, -1);
    std::vector<Child> pref(n + 1);
    bfs_order.reserve(n);
    for (auto root = 0; root < n; ++root) {
        if (~parent[root]) {
            continue;
        }
        parent[root] = root;
        bfs_order.clear();
        bfs_order.push_back(root);
        auto q = bfs_order.cbegin();
        while (q != bfs_order.cend()) {
            auto u = *q++;
            for (auto [v, w] : g[u]) {
                if (v != parent[u]) {
                    parent[v] = u;
                    bfs_order.push_back(v);
                }
            }
        }
        for (auto u : bfs_order | std::views::reverse) {
            Child sum = e();
            for (auto [v, w] : g[u]) {
                if (v != parent[u]) {
                    sum = rake(sum, add_edge(dp[v], w));
                }
            }
            dp[u] = add_vertex(sum, u);
        }
        for (auto u : bfs_order) {
            auto i = 0;
            pref[0] = e();
            for (auto [v, w] : g[u]) {
                auto state = (v == parent[u]) ? dp_parent[u] : dp[v];
                pref[i + 1] = rake(pref[i], add_edge(state, w));
                ++i;
            }
            auto suff = e();
            for (auto [v, w] : g[u] | std::views::reverse) {
                if (v != parent[u]) {
                    Child except_child = rake(pref[i - 1], suff);
                    dp_parent[v] = add_vertex(except_child, u);
                }
                auto state = (v == parent[u]) ? dp_parent[u] : dp[v];
                suff = rake(add_edge(state, w), suff);
                --i;
            }
            dp[u] = add_vertex(suff, u);
        }
    }
    return dp;
}

#endif // REROOTING_HPP

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<vector<pair<int, int>>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        auto w = A[u] ^ A[v];
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    struct S {
        int sz;
        i64 sum;
    };
    auto rake = [&](S l, S r) -> S {
        S a;
        a.sz = l.sz + r.sz;
        a.sum = l.sum + r.sum;
        return a;
    };
    auto add_edge = [&](S d, int w) -> S {
        S a;
        a.sz = d.sz;
        a.sum = d.sum + i64(a.sz) * w;
        return a;
    };
    auto add_vertex = [&](S d, int) -> S {
        S a;
        a.sz = d.sz + 1;
        a.sum = d.sum;
        return a;
    };
    auto e = [] { return S{0, 0}; };
    auto dp = rerooting(adj, rake, add_edge, add_vertex, e);
    auto f = [](S a) { return a.sum; };
    show(dp | views::transform(f));
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
