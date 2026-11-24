#include <bits/stdc++.h>
using namespace std;

template <typename T> struct csr_graph {
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
        return ranges::subrange(csr_.begin() + start_[u], csr_.begin() + start_[u + 1]);
    }
    int size() const { return n_; }

private:
    int n_;
    bool built_ = false;
    vector<Edge> edges_;
    vector<Arc> csr_;
    vector<int> start_;
};

template <typename T> pair<bool, vector<T>> goldberg_radzik(const auto &g, int src = 0) {
    constexpr auto inf = numeric_limits<T>::max() / 2;
    auto n = int(g.size());
    vector<T> dist(n, inf);
    dist[src] = 0;
    vector<int> cur{src}, nxt;
    vector<int> state(n); // t: in stack/pool, -t: complete
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
            if (can_relax && !dfs(u)) {
                return {false, {}};
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
    return {true, dist};
}

void solve() {
    int N, L, R, K;
    cin >> N >> L >> R >> K;
    vector<int> A(N + 1);
    for (auto i = 1; i <= N; ++i) {
        cin >> A[i];
    }
    csr_graph<int> g(N + 1);
    for (auto i = 1; i < N; ++i) {
        if (A[i] < A[i + 1]) {
            g.add_edge(i, i + 1, -1);
            g.add_edge(i + 1, i, K);
        } else if (A[i] > A[i + 1]) {
            g.add_edge(i, i + 1, K);
            g.add_edge(i + 1, i, -1);
        } else {
            g.add_edge(i, i + 1, 0);
            g.add_edge(i + 1, i, 0);
        }
    }
    for (auto i = 1; i <= N; ++i) {
        g.add_edge(0, i, -L);
        g.add_edge(i, 0, R);
    }
    g.build();
    auto [ok, d] = goldberg_radzik<int>(g);
    if (!ok) {
        cout << "-1\n";
        return;
    }
    for (auto i = 1; i <= N; ++i) {
        cout << -d[i] << " ";
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
