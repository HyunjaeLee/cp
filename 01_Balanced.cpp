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
        return ranges::subrange(csr_.begin() + start_[u], csr_.begin() + start_[u + 1]);
    }
    int size() const { return n_; }

private:
    int n_;
    bool built_ = false;
    vector<tuple<int, int, T>> edges_;
    vector<pair<int, T>> csr_;
    vector<int> start_;
};

template <typename T, T inf = numeric_limits<T>::max() / 2>
tuple<bool, vector<T>, vector<int>> goldberg_radzik(const auto &g, int src) {
    auto n = int(g.size());
    vector<T> dist(n, inf);
    dist[src] = 0;
    vector<int> cur{src}, nxt, order, parent(n, -1);
    vector<int> state(n); // -t: in stack/labeled, t: complete
    for (auto t = 1; !cur.empty(); ++t) {
        order.clear();
        auto dfs = [&](this auto &&self, int u) {
            if (state[u] == t || state[u] == -t)
                return state[u] == t;
            state[u] = -t;
            for (auto [v, w] : g[u]) {
                if (dist[v] <= dist[u] + w)
                    continue;
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (!self(v))
                    return false;
            }
            state[u] = t;
            order.push_back(u);
            return true;
        };
        for (auto u : cur) {
            if (state[u] == t)
                continue;
            auto can_relax = false;
            for (auto [v, w] : g[u]) {
                if (dist[u] + w < dist[v]) {
                    can_relax = true;
                    break;
                }
            }
            if (can_relax && !dfs(u)) {
                return {false, {}, {}};
            }
        }
        nxt.clear();
        for (auto u : order | views::reverse) {
            for (auto [v, w] : g[u]) {
                if (dist[v] <= dist[u] + w)
                    continue;
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (state[v] != -t) {
                    state[v] = -t;
                    nxt.push_back(v);
                }
            }
        }
        swap(cur, nxt);
    }
    return {true, std::move(dist), std::move(parent)};
}

void solve() {
    int N, M;
    cin >> N >> M;
    csr_graph<int> g(N + 1);
    for (auto i = 0; i < M; ++i) {
        int l, r;
        cin >> l >> r;
        g.add_edge(l - 1, r, (r - l + 1) / 2);
        g.add_edge(r, l - 1, -(r - l + 1) / 2);
    }
    for (auto i = 0; i < N; ++i) {
        g.add_edge(i, i + 1, 1);
        g.add_edge(i + 1, i, 0);
    }
    g.build();
    auto [ok, A, parent] = goldberg_radzik<int>(g, 0);
    for (auto i = N - 1; 0 <= i; --i) {
        A[i + 1] = (A[i + 1] - A[i]) ^ 1;
    }
    show(A | views::drop(1), "");
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
