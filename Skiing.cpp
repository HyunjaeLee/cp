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

template <typename T = int> struct csr_graph {
    struct Edge {
        int u;
        int v;
        T w;
    };
    struct Arc {
        int v;
        T w;
    };
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
        for (const auto &e : edges_) {
            ++start_[e.u + 1];
        }
        for (int i = 0; i < n_; ++i) {
            start_[i + 1] += start_[i];
        }
        auto pos = start_;
        for (const auto &e : edges_) {
            csr_[pos[e.u]++] = {e.v, e.w};
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
    std::vector<Arc> csr_;
    std::vector<int> start_;
};

auto goldberg_radzik(const auto &g, int src = 0) {
    constexpr auto inf = numeric_limits<i64>::max() / 2;
    auto N = int(g.size());
    vector<i64> dist(N, inf);
    dist[src] = 0;
    vector<int> cur{src}, nxt;
    vector<int> state(N); // t: in stack/pool, -t: complete
    vector<int> order;    // postorder
    for (auto t = 1; !cur.empty(); ++t) {
        // toposort
        order.clear();
        auto dfs = [&](this auto &&self, int u) -> bool {
            if (abs(state[u]) == t)
                return state[u] < 0;
            state[u] = t;
            for (auto [v, w] : g[u]) {
                if (dist[u] + w >= dist[v])
                    continue;
                dist[v] = dist[u] + w;
                if (!self(v))
                    return false; // found negative cycle
            }
            state[u] = -t;
            order.push_back(u);
            return true;
        };
        for (auto u : cur) {
            auto can_relax = false;
            for (auto [v, w] : g[u]) {
                if (dist[u] + w < dist[v]) {
                    can_relax = true;
                    break;
                }
            }
            if (can_relax) {
                auto ok = dfs(u);
                assert(ok); // no negative cycle
            }
        }
        nxt.clear();
        for (auto u : order | views::reverse) {
            for (auto [v, w] : g[u]) {
                if (dist[u] + w >= dist[v])
                    continue;
                dist[v] = dist[u] + w;
                if (state[v] != t) {
                    state[v] = t;
                    nxt.push_back(v);
                }
            }
        }
        swap(cur, nxt);
    }
    return dist;
}

void solve() {
    int N, M;
    cin >> N >> M;
    vector<i64> A(N);
    read(A);
    csr_graph<i64> g(N);
    auto add_edge = [&](int u, int v) {
        auto w = A[v] - A[u];
        if (0 < w) {
            w *= 2;
        }
        g.add_edge(u, v, w);
    };
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        add_edge(u, v);
        add_edge(v, u);
    }
    g.build();
    auto d = goldberg_radzik(g);
    auto ans = -ranges::min(d);
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
