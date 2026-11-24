#include <atcoder/lazysegtree>
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

#ifndef HEAVY_LIGHT_DECOMPOSITION_HPP
#define HEAVY_LIGHT_DECOMPOSITION_HPP

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <vector>

struct heavy_light_decomposition {
    heavy_light_decomposition(const std::vector<std::vector<int>> &graph, int root)
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
    int depth(int u) const {
        assert(0 <= u && u < n_);
        return depth_[u];
    };
    int size(int u) const {
        assert(0 <= u && u < n_);
        return size_[u];
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
    std::vector<std::vector<int>> graph_;
    std::vector<int> size_, depth_, parent_, top_, in_, out_;
};

#endif // HEAVY_LIGHT_DECOMPOSITION_HPP

struct S {
    i64 sum, sz;
};

S op(S a, S b) { return {a.sum + b.sum, a.sz + b.sz}; }

S e() { return {0, 0}; }

using F = i64;

S mapping(F f, S x) { return {x.sum + x.sz * f, x.sz}; }

F composition(F f, F g) { return f + g; }

F id() { return 0; }

void solve() {
    int N;
    cin >> N;
    vector<pair<int, int>> E(N - 1);
    vector<vector<int>> adj(N);
    for (auto &[u, v] : E) {
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    heavy_light_decomposition hld(adj, 0);
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(vector<S>(N, {0, 1}));
    for (auto i = 0; i < N - 1; ++i) {
        auto w = i + 1;
        auto [p, u] = E[i];
        if (hld.lca(p, u) != p) {
            swap(p, u);
        }
        if (N - hld.size(u) < hld.size(u)) {
            hld.access_subtree(u, true, [&](int l, int r) { seg.apply(l, r, w); });
        } else {
            seg.apply(0, N, w);
            hld.access_subtree(u, true, [&](int l, int r) { seg.apply(l, r, -w); });
        }
    }
    vector<i64> ans(N);
    for (auto i = 0; i < N; ++i) {
        hld.access_node(i, [&](int p) { ans[i] = seg.get(p).sum; });
    }
    show(ans);
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
