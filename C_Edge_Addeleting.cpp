// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;

#ifndef HEAVY_LIGHT_DECOMPOSITION_HPP
#define HEAVY_LIGHT_DECOMPOSITION_HPP

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <vector>

template <typename G> struct heavy_light_decomposition {
    heavy_light_decomposition(const G &graph, int root)
        : n_(int(graph.size())), timer_(0), graph_(graph), size_(n_, 1), depth_(n_), parent_(n_, -1), top_(n_), in_(n_),
          out_(n_) {
        assert(0 <= root && root < n_);
        top_[root] = root;
        dfs_size(root);
        dfs_hld(root);
    }
    template <typename Function> void access_node(int u, Function f) const {
        assert(0 <= u && u < n_);
        f(in_[u]);
    }
    template <typename Function>
    std::enable_if_t<std::is_same_v<std::invoke_result_t<Function, int, int>, void>, void>
    access_path(int u, int v, bool include_lca, Function f) const {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        while (top_[u] != top_[v]) {
            if (depth_[top_[u]] < depth_[top_[v]]) {
                std::swap(u, v);
            }
            f(in_[top_[u]], in_[u] + 1);
            u = parent_[top_[u]];
        }
        if (depth_[u] > depth_[v]) {
            std::swap(u, v);
        }
        if (include_lca) {
            f(in_[u], in_[v] + 1);
        } else {
            f(in_[u] + 1, in_[v] + 1);
        }
    }
    template <typename Function>
    std::enable_if_t<std::is_same_v<std::invoke_result_t<Function, int, int, bool>, void>, void>
    access_path(int u, int v, bool include_lca, Function f) const {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        bool u_to_lca = true;
        while (top_[u] != top_[v]) {
            if (depth_[top_[u]] < depth_[top_[v]]) {
                std::swap(u, v);
                u_to_lca = !u_to_lca;
            }
            f(in_[top_[u]], in_[u] + 1, u_to_lca);
            u = parent_[top_[u]];
        }
        if (depth_[u] > depth_[v]) {
            std::swap(u, v);
        } else {
            u_to_lca = !u_to_lca;
        }
        if (include_lca) {
            f(in_[u], in_[v] + 1, u_to_lca);
        } else {
            f(in_[u] + 1, in_[v] + 1, u_to_lca);
        }
    }
    template <typename Function> void access_subtree(int u, bool include_root, Function f) const {
        assert(0 <= u && u < n_);
        if (include_root) {
            f(in_[u], out_[u]);
        } else {
            f(in_[u] + 1, out_[u]);
        }
    }
    int lca(int u, int v) const {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        while (top_[u] != top_[v]) {
            if (depth_[top_[u]] < depth_[top_[v]]) {
                std::swap(u, v);
            }
            u = parent_[top_[u]];
        }
        if (depth_[u] > depth_[v]) {
            std::swap(u, v);
        }
        return u;
    }
    int in(int u) const {
        assert(0 <= u && u < n_);
        return in_[u];
    }
    int out(int u) const {
        assert(0 <= u && u < n_);
        return out_[u];
    }
    int size(int u) const {
        assert(0 <= u && u < n_);
        return size_[u];
    };
    int depth(int u) const {
        assert(0 <= u && u < n_);
        return depth_[u];
    };
    int parent(int u) const {
        assert(0 <= u && u < n_);
        return parent_[u];
    };

private:
    void dfs_size(int u) {
        for (auto &v : graph_[u]) {
            if (v != parent_[u]) {
                depth_[v] = depth_[u] + 1;
                parent_[v] = u;
                dfs_size(v);
                size_[u] += size_[v];
                if (size_[graph_[u][0]] < size_[v] || graph_[u][0] == parent_[u]) {
                    std::swap(graph_[u][0], v);
                }
            }
        }
    }
    void dfs_hld(int u) {
        in_[u] = timer_++;
        for (auto v : graph_[u]) {
            if (v != parent_[u]) {
                top_[v] = (v == graph_[u][0] ? top_[u] : v);
                dfs_hld(v);
            }
        }
        out_[u] = timer_;
    }
    const int n_;
    int timer_;
    G graph_;
    std::vector<int> size_, depth_, parent_, top_, in_, out_;
};

#endif // HEAVY_LIGHT_DECOMPOSITION_HPP

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

#define TC
void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> d(N), p(N, -1);
    [&](this auto &&self, int u) -> void {
        for (auto v : adj[u]) {
            if (v == p[u])
                continue;
            d[v] = d[u] + 1;
            p[v] = u;
            self(v);
        }
    }(0);
    heavy_light_decomposition hld(adj, 0);
    auto ans = d[N - 1];
    while (Q--) {
        int v;
        cin >> v;
        --v;
        auto l = hld.lca(N - 1, v);
        if (l == 0)
            continue;
        auto dist = d[N - 1] + d[v] - 2 * d[l] + 1;
        ans = max(dist, ans);
    }
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
