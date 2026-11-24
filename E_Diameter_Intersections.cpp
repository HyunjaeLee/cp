#include <atcoder/convolution>
#include <bits/stdc++.h>
using namespace atcoder;
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

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

// requires non-negative edge weights
// return (diameter, path)
// for an unweighted tree, centers are path[d / 2] and path[(d + 1) / 2]
template <typename EdgeWeight> auto tree_diameter(const CSRGraph<EdgeWeight> &g) {
    assert(0 < g.size());
    auto n = int(g.size());
    vector<int> parent(n, -1);
    vector<EdgeWeight> depth(n);
    auto dfs = [&](int x) {
        vector<int> st;
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
        auto it = ranges::max_element(depth);
        auto r = int(it - depth.begin());
        return pair(r, *it);
    };
    auto x = dfs(0).first;
    auto [y, d] = dfs(x);
    vector<int> path;
    for (auto u = y; ~u; u = parent[u]) {
        path.push_back(u);
    }
    return pair(d, path);
}

#define TC
void solve() {
    int N;
    cin >> N;
    CSRGraph<> G(N);
    for (auto i = 1; i < N; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        G.add_edge(u, v);
    }
    G.build_undirected();
    auto [D, P] = tree_diameter(G);
    auto dfs = [&](this auto &&self, int u, int p, int d, vector<i64> &a) -> int {
        if (d == D / 2) {
            return 1;
        }
        auto cnt = 0;
        for (auto e : G[u]) {
            if (e.v == p)
                continue;
            cnt += self(e.v, u, d + 1, a);
        }
        if (2 <= cnt) {
            a[d] = 1;
        }
        return cnt ? 1 : 0;
    };
    vector<i64> A(D / 2 + 1), B(D / 2 + 1);
    A[D / 2] = B[D / 2] = 1;
    auto x = P[D / 2];
    auto y = P[(D + 1) / 2];
    dfs(x, y, 0, A);
    dfs(y, x, 0, B);
    auto C = convolution_ll(convolution_ll(A, {0, 1}), B);
    vector<int> ans;
    for (auto i = 0; i < int(C.size()); ++i) {
        if (0 < C[i]) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << " ";
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
