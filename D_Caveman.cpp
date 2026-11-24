#include <atcoder/dsu>
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

// requires non-negative edge weights
// return (diameter, path)
// for an unweighted tree, centers are path[d / 2] and path[(d + 1) / 2]
template <typename T> auto tree_diameter(const auto &g) {
    assert(0 < g.size());
    auto n = int(g.size());
    std::vector<int> parent(n, -1);
    std::vector<T> depth(n);
    auto dfs = [&](int x) {
        std::vector<int> st;
        st.push_back(x);
        parent[x] = -1;
        depth[x] = 0;
        while (!st.empty()) {
            auto u = st.back();
            st.pop_back();
            for (auto [v, w] : g[u]) {
                if (v != parent[u]) {
                    st.push_back(v);
                    parent[v] = u;
                    depth[v] = depth[u] + w;
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

template <typename T> struct csr_graph {
    csr_graph(int n) : n_(n) {}
    void add_edge(int u, int v, T w) {
        assert(!built_);
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        edges_.push_back({u, v, w});
    }
    void build() {
        assert(!built_);
        start_.assign(n_ + 1, 0);
        csr_.resize(edges_.size());
        for (auto [u, v, w] : edges_) {
            ++start_[u + 1];
        }
        for (int i = 0; i < n_; ++i) {
            start_[i + 1] += start_[i];
        }
        auto pos = start_;
        for (auto [u, v, w] : edges_) {
            csr_[pos[u]++] = {v, w};
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
    std::vector<std::tuple<int, int, T>> edges_;
    std::vector<std::pair<int, T>> csr_;
    std::vector<int> start_;
};

#define TC
void solve() {
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> E(M);
    vector<int> deg(N);
    for (auto &[u, v] : E) {
        cin >> u >> v;
        --u, --v;
        deg[u]++;
        deg[v]++;
    }
    for (auto i = 0; i < N; ++i) {
        if (deg[i] == 0) {
            cout << "Brain Melt\n";
            return;
        }
    }
    atcoder::dsu dsu(N);
    auto is_tree = true;
    for (auto [u, v] : E) {
        if (dsu.same(u, v)) {
            is_tree = false;
        } else {
            dsu.merge(u, v);
        }
    }
    if (dsu.size(0) == N && is_tree) {
        csr_graph<int> g(N);
        for (auto [u, v] : E) {
            g.add_edge(u, v, 1);
            g.add_edge(v, u, 1);
        }
        g.build();
        auto d = tree_diameter<int>(g).first;
        if (d <= 2) {
            cout << "2\n";
        } else {
            cout << "Many\n";
        }
    } else {
        cout << "Many\n";
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
