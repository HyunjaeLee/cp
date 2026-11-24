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

#line 1 "graph/auxiliary_tree.hpp"

#line 1 "heavy_light_decomposition/heavy_light_decomposition.hpp"

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

#line 6 "graph/auxiliary_tree.hpp"
#include <utility>
#line 8 "graph/auxiliary_tree.hpp"

struct AuxiliaryTree {
    AuxiliaryTree(const std::vector<std::vector<int>> &graph, int root) : hld_(graph, root) {}
    std::vector<std::pair<int, int>> get(std::vector<int> x) const {
        if (x.empty()) {
            return {};
        }
        std::ranges::sort(x, {}, [&](int u) { return hld_.in(u); });
        const auto m = int(x.size());
        for (auto i = 1; i < m; i++) {
            x.push_back(hld_.lca(x[i - 1], x[i]));
        }
        std::ranges::sort(x, {}, [&](int u) { return hld_.in(u); });
        auto r = std::ranges::unique(x);
        x.erase(r.begin(), r.end());
        const auto n = int(x.size());
        std::vector<int> st;
        std::vector<std::pair<int, int>> dfs_order(n);
        st.push_back(x[0]);
        dfs_order[0] = {x[0], -1};
        for (auto i = 1; i < n; ++i) {
            auto v = x[i];
            while (!st.empty()) {
                auto u = st.back();
                if (hld_.in(v) < hld_.out(u)) {
                    break;
                } else {
                    st.pop_back();
                }
            }
            auto parent = st.back();
            dfs_order[i] = {v, parent};
            st.push_back(v);
        }
        return dfs_order;
    }
    const heavy_light_decomposition &hld() const { return hld_; }

private:
    const heavy_light_decomposition hld_;
};

#define TC
void solve() {
    int N, K, S, Q;
    cin >> N >> K >> S >> Q;
    vector<vector<int>> adj(N);
    vector<pair<int, int>> E(N - 1);
    for (auto &[u, v] : E) {
        cin >> u >> v;
        --u, --v;
        if (u > v)
            swap(u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ranges::sort(E);
    vector<vector<int>> F(K);
    for (auto i = 0; i < S; ++i) {
        int u, x;
        cin >> u >> x;
        --u, --x;
        F[x].push_back(u);
    }
    vector<vector<int>> G(N);
    auto gid = 0;
    AuxiliaryTree aux(adj, 0);
    vector<int> real(N);
    for (auto c = 0; c < K; ++c) {
        for (auto u : F[c])
            real[u] = 1;
        for (auto [u, p] : aux.get(F[c])) {
            if (!real[u])
                continue;
            if (p == -1) {
                G[u].push_back(gid++);
                continue;
            }
            if (real[p] && ranges::binary_search(E, minmax(u, p))) {
                G[u].push_back(G[p].back());
            } else {
                G[u].push_back(gid++);
            }
        }
        for (auto u : F[c])
            real[u] = 0;
    }
    map<pair<int, int>, int> mp;
    vector<pair<int, int>> qs(Q);
    vector<vector<int>> H(N);
    for (auto &[u, v] : qs) {
        cin >> u >> v;
        --u, --v;
        if (size(G[u]) < size(G[v])) {
            swap(u, v);
        }
        H[u].push_back(v);
    }
    vector<int> in(gid);
    for (auto u = 0; u < N; ++u) {
        for (auto i : G[u]) {
            in[i] = 1;
        }
        ranges::sort(H[u]);
        H[u].erase(unique(begin(H[u]), end(H[u])), end(H[u]));
        for (auto v : H[u]) {
            auto cnt = 0;
            for (auto i : G[v]) {
                if (in[i]) {
                    cnt++;
                }
            }
            mp[{u, v}] = cnt;
        }
        for (auto i : G[u]) {
            in[i] = 0;
        }
    }
    for (auto [u, v] : qs) {
        cout << mp[{u, v}] << " ";
    }
    cout << "\n";
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
