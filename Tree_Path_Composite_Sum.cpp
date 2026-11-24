#include <atcoder/modint>
#include <bits/stdc++.h>
using Z = atcoder::modint998244353;

/*
    vector<vector<pair<int, EdgeWeight>>> g;
    struct Subtree {};
    struct Children {};
    auto rake = [&](Children l, Children r) -> Children {};
    auto add_edge = [&](Subtree d, EdgeWeight w) -> Children {};
    auto add_vertex = [&](Children d, int i) -> Subtree {};
    auto e = []() -> Children {};
*/

auto reroot_dfs(const auto &g, auto rake, auto add_edge, auto add_vertex, auto e) {
    using Children = decltype(e());
    using Subtree = decltype(add_vertex(e(), 0));
    std::vector<Subtree> dp(g.size());
    auto dfs0 = [&](auto &&self, int u, int p) -> Subtree {
        Children sum = e();
        for (auto [v, w] : g[u]) {
            if (v != p) {
                sum = rake(sum, add_edge(self(self, v, u), w));
            }
        }
        return dp[u] = add_vertex(sum, u);
    };
    auto dfs1 = [&](auto &&self, int u, int p) -> void {
        std::vector<Children> pref{e()};
        for (auto [v, w] : g[u]) {
            pref.push_back(rake(pref.back(), add_edge(dp[v], w)));
        }
        Children suff = e();
        for (auto i = int(g[u].size()) - 1; 0 <= i; --i) {
            auto [v, w] = g[u][i];
            auto x = add_edge(dp[v], w);
            if (v != p) {
                dp[u] = add_vertex(rake(pref[i], suff), u);
                self(self, v, u);
            }
            suff = rake(x, suff);
        }
        dp[u] = add_vertex(suff, u);
    };
    dfs0(dfs0, 0, 0);
    dfs1(dfs1, 0, 0);
    return dp;
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    using EdgeWeight = std::pair<int, int>;
    std::vector<std::vector<std::pair<int, EdgeWeight>>> g(N);
    std::vector<int> a(N);
    for (auto i = 0; i < N; ++i) {
        std::cin >> a[i];
    }
    for (auto i = 0; i < N - 1; ++i) {
        int u, v, b, c;
        std::cin >> u >> v >> b >> c;
        g[u].push_back({v, {b, c}});
        g[v].push_back({u, {b, c}});
    }
    using Subtree = std::pair<Z, int>;
    using Children = std::pair<Z, int>;
    auto rake = [&](Children l, Children r) -> Children { return {l.first + r.first, l.second + r.second}; };
    auto add_edge = [&](Subtree d, EdgeWeight w) -> Children {
        return {w.first * d.first + Z::raw(w.second) * d.second, d.second};
    };
    auto add_vertex = [&](Children d, int i) -> Subtree { return {d.first + a[i], d.second + 1}; };
    auto e = []() -> Children { return {0, 0}; };
    auto dp = reroot_dfs(g, rake, add_edge, add_vertex, e);
    for (auto [sum, cnt] : dp) {
        std::cout << sum.val() << ' ';
    }
}
