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

auto reroot_dfs(const auto &g, auto rake, auto add_edge, auto add_vertex, auto e) {
    using Child = decltype(e());
    using Subtree = decltype(add_vertex(e(), 0));
    vector<Subtree> dp(g.size());
    [&](this auto &&self, int u, int p) -> Subtree {
        Child sum = e();
        for (auto [v, w] : g[u]) {
            if (v != p) {
                sum = rake(sum, add_edge(self(v, u), w));
            }
        }
        return dp[u] = add_vertex(sum, u);
    }(0, 0);
    [&](this auto &&self, int u, int p) -> void {
        vector<Child> pref{e()};
        for (auto [v, w] : g[u]) {
            pref.push_back(add_edge(dp[v], w));
        }
        auto suff = pref;
        inclusive_scan(pref.begin(), pref.end(), pref.begin(), rake);
        exclusive_scan(suff.rbegin(), suff.rend(), suff.rbegin(), e(), rake);
        for (auto i = 0; i < int(g[u].size()); ++i) {
            if (auto [v, w] = g[u][i]; v != p) {
                dp[u] = add_vertex(rake(pref[i], suff[i + 1]), u);
                self(v, u);
            }
        }
        dp[u] = add_vertex(suff[0], u);
    }(0, 0);
    return dp;
}

#define TC
void solve() {
    int K;
    cin >> K;
    vector<int> major(K, -1), minor(K, -1);
    for (auto i = 0; i < K; ++i) {
        int N;
        cin >> N;
        vector<vector<pair<int, int>>> adj(N);
        for (auto j = 0; j < N - 1; ++j) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].emplace_back(v, 1);
            adj[v].emplace_back(u, 1);
        }
        using Child = array<int, 3>; // 0: subtree root not included, 1: subtree root included
        using Subtree = array<int, 2>;
        auto rake = [&](Child l, Child r) -> Child {
            Child c{};
            c[0] = l[0] + r[0];
            c[1] = l[1] + r[1];
            c[2] = ranges::max(l) + ranges::max(r);
            return c;
        };
        auto add_edge = [&](Subtree d, auto) -> Child { return {d[0], d[1]}; };
        auto add_vertex = [&](Child d, int) -> Subtree { return {d[2], d[0] + 1}; };
        auto e = []() -> Child { return {}; };
        auto dp = reroot_dfs(adj, rake, add_edge, add_vertex, e);
        auto root = 0;
        for (auto j = 0; j < N; ++j) {
            if (dp[root][1] < dp[j][1]) {
                root = j;
            }
        }
        major[i] = root;
        for (auto [v, w] : adj[root]) {
            minor[i] = v;
        }
    }
    auto root = -1;
    for (auto i = 0; i < K; ++i) {
        if (minor[i] != -1) {
            root = i;
        }
    }
    for (auto i = 0; i < K; ++i) {
        assert(major[i] != -1);
    }
    if (root == -1) {
        for (auto i = 1; i < K; ++i) {
            cout << 1 << " " << major[0] + 1 << " " << i + 1 << " " << major[i] + 1 << "\n";
        }
        return;
    }
    for (auto i = 0; i < K; ++i) {
        if (root == i)
            continue;
        cout << root + 1 << " " << minor[root] + 1 << " " << i + 1 << " " << major[i] + 1 << "\n";
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
