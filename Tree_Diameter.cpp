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

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    std::vector<std::vector<std::pair<int, int>>> g(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    auto rake = [&](long long l, long long r) -> long long { return std::max(l, r); };
    auto add_edge = [&](long long d, int w) -> long long { return d + w; };
    auto add_vertex = [&](long long d, int) -> long long { return d; };
    auto e = []() -> long long { return 0; };
    auto dp = rerooting(g, rake, add_edge, add_vertex, e);
    auto root = 0;
    for (auto i = 0; i < N; ++i) {
        if (dp[root] < dp[i]) {
            root = i;
        }
    }
    std::vector<int> parent(N, -1);
    std::vector<long long> depth(N);
    auto dfs = [&](auto &&self, int u) -> void {
        for (auto [v, w] : g[u]) {
            if (v == parent[u]) {
                continue;
            }
            parent[v] = u;
            depth[v] = depth[u] + w;
            self(self, v);
        }
    };
    dfs(dfs, root);
    auto u = 0;
    for (auto i = 0; i < N; ++i) {
        if (depth[u] < depth[i]) {
            u = i;
        }
    }
    std::vector<int> path;
    while (u != -1) {
        path.push_back(u);
        u = parent[u];
    }
    std::cout << dp[root] << " " << path.size() << "\n";
    for (auto v : path) {
        std::cout << v << " ";
    }
}
