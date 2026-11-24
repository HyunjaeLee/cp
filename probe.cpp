#include <bits/stdc++.h>
using namespace std;

#ifndef CSR_GRAPH_HPP
#define CSR_GRAPH_HPP

#include <cassert>
#include <ranges>
#include <vector>

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

#endif // CSR_GRAPH_HPP

#ifndef GOLDBERG_RADZIK_HPP
#define GOLDBERG_RADZIK_HPP

#include <limits>
#include <ranges>
#include <tuple>
#include <utility>
#include <vector>

template <typename T, T inf = std::numeric_limits<T>::max() / 2>
std::tuple<bool, std::vector<T>, std::vector<int>> goldberg_radzik(const auto &g, int src) {
    auto n = int(g.size());
    std::vector<T> dist(n, inf);
    dist[src] = 0;
    std::vector<int> cur{src}, nxt, order, parent(n, -1);
    std::vector<int> state(n); // -t: in stack/labeled, t: visited
    for (auto t = 1; !cur.empty(); ++t) {
        order.clear();
        auto dfs = [&](auto &&self, int u) {
            if (state[u] == t || state[u] == -t) {
                return state[u] == t;
            }
            state[u] = -t;
            for (auto [v, w] : g[u]) {
                if (dist[v] <= dist[u] + w) {
                    continue;
                }
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (!self(self, v)) {
                    return false;
                }
            }
            state[u] = t;
            order.push_back(u);
            return true;
        };
        for (auto u : cur) {
            if (state[u] == t) {
                continue;
            }
            auto can_relax = false;
            for (auto [v, w] : g[u]) {
                if (dist[u] + w < dist[v]) {
                    can_relax = true;
                    break;
                }
            }
            if (can_relax && !dfs(dfs, u)) {
                return {false, {}, {}};
            }
        }
        nxt.clear();
        for (auto u : order | std::views::reverse) {
            for (auto [v, w] : g[u]) {
                if (dist[v] <= dist[u] + w) {
                    continue;
                }
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (state[v] != -t) {
                    state[v] = -t;
                    nxt.push_back(v);
                }
            }
        }
        std::swap(cur, nxt);
    }
    return {true, std::move(dist), std::move(parent)};
}

#endif // GOLDBERG_RADZIK_HPP

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    csr_graph<int> g(N + 1);
    for (auto i = 0; i < M; ++i) {
        int x, y, r;
        cin >> x >> y >> r;
        g.add_edge(x - 1, y, r);
        g.add_edge(y, x - 1, -r);
    }
    for (auto i = 0; i < N; ++i) {
        g.add_edge(i, i + 1, 1);
        g.add_edge(i + 1, i, 0);
    }
    g.build();
    auto [ok, A, _] = goldberg_radzik<int>(g, 0);
    if (!ok) {
        cout << "NONE\n";
        return 0;
    }
    for (auto i = N - 1; 0 <= i; --i) {
        A[i + 1] -= A[i];
    }
    string ans;
    for (auto i = 1; i <= N; ++i) {
        ans += A[i] ? '#' : '-';
    }
    cout << ans << "\n";
}
