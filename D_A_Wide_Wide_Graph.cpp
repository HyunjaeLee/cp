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

#line 1 "tree/tree_diameter.hpp"

#line 1 "graph/csr_graph.hpp"

#include <cassert>
#include <ranges>
#include <vector>

template <typename EdgeWeight = int> struct CSRGraph {
    struct Edge {
        int u;
        int v;
        EdgeWeight w;
        int i;
    };
    CSRGraph(int n) : n_(n) {}
    void add_edge(int u, int v, EdgeWeight w = 1) {
        assert(!built_);
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        auto i = int(edges_.size());
        edges_.push_back({u, v, w, i});
    }
    void build_undirected() {
        assert(!built_);
        start_.assign(n_ + 1, 0);
        csr_.resize(2 * edges_.size());
        for (const auto &e : edges_) {
            ++start_[e.u + 1];
            ++start_[e.v + 1];
        }
        for (int i = 0; i < n_; ++i) {
            start_[i + 1] += start_[i];
        }
        auto pos = start_;
        for (const auto &e : edges_) {
            csr_[pos[e.u]++] = {e.u, e.v, e.w, e.i};
            csr_[pos[e.v]++] = {e.v, e.u, e.w, e.i};
        }
        built_ = true;
    }
    void build_directed() {
        assert(!built_);
        start_.assign(n_ + 1, 0);
        csr_.resize(edges_.size());
        for (const auto &e : edges_) {
            ++start_[e.u + 1];
        }
        for (int i = 0; i < n_; ++i) {
            start_[i + 1] += start_[i];
        }
        auto pos = start_;
        for (const auto &e : edges_) {
            csr_[pos[e.u]++] = e;
        }
        built_ = true;
    }
    auto operator[](int u) const {
        assert(built_);
        assert(0 <= u && u < n_);
        return std::ranges::subrange(csr_.begin() + start_[u], csr_.begin() + start_[u + 1]);
    }
    int size() const { return n_; }

private:
    int n_;
    bool built_ = false;
    std::vector<Edge> edges_;
    std::vector<Edge> csr_;
    std::vector<int> start_;
};

#line 5 "tree/tree_diameter.hpp"
#include <algorithm>
#line 8 "tree/tree_diameter.hpp"

// requires non-negative edge weights
// return (diameter, path)
// for an unweighted tree, centers are path[d / 2] and path[(d + 1) / 2]
template <typename EdgeWeight> auto tree_diameter(const CSRGraph<EdgeWeight> &g) {
    assert(0 < g.size());
    auto n = int(g.size());
    std::vector<int> parent(n, -1);
    std::vector<EdgeWeight> depth(n);
    auto dfs = [&](int x) {
        std::vector<int> st;
        st.push_back(x);
        parent[x] = -1;
        depth[x] = 0;
        while (!st.empty()) {
            auto u = st.back();
            st.pop_back();
            for (const auto &e : g[u]) {
                if (e.v != parent[u]) {
                    st.push_back(e.v);
                    parent[e.v] = u;
                    depth[e.v] = depth[u] + e.w;
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

void solve() {
    int N;
    cin >> N;
    CSRGraph<> g(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g.add_edge(u, v);
    }
    g.build_undirected();
    auto [d, path] = tree_diameter(g);
    auto x = path[d / 2];
    auto y = path[(d + 1) / 2];
    vector<int> R(N);
    auto dfs = [&](this auto &&self, int u, int p) -> void {
        for (auto e : g[u]) {
            if (e.v == p)
                continue;
            R[e.v] = R[u] + 1;
            self(e.v, u);
        }
    };
    dfs(x, y);
    dfs(y, x);
    map<int, int> mp;
    for (auto i = 0; i < N; ++i) {
        mp[R[i]]++;
    }
    auto V = N + 1;
    vector<int> ans(1 + N);
    for (auto i = N; 1 <= i; --i) {
        V -= mp[i - (d + 1) / 2];
        ans[i] = min(V, N);
    }
    show(ans | views::drop(1));
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
