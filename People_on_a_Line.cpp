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

struct Edge {
    int u, v;
    i64 w;
};
struct Arc {
    int v;
    i64 w;
};

// Equivalent to a zero-weight super-source connected to every vertex.
// For a feasible graph, potential satisfies w + p[u] - p[v] >= 0.
// Input weights must fit the checked range; all ARC232 weights easily do.
template <class EdgeList> bool has_negative_cycle(int n, const EdgeList &edges, std::vector<i64> *potential = nullptr) {
    if (n < 0)
        throw std::invalid_argument("vertex count");
    const i64 weight_limit = std::numeric_limits<i64>::max() / 4 / std::max(1, n);
    i64 negative = 0;
    std::vector<int> begin(n + 1);
    for (const auto &e : edges) {
        if (e.u < 0 || e.u >= n || e.v < 0 || e.v >= n)
            throw std::invalid_argument("vertex index");
        if (e.w < -weight_limit || e.w > weight_limit)
            throw std::overflow_error("weight range");
        negative = std::max(negative, -i64(e.w));
        ++begin[e.u + 1];
    }
    std::vector<i64> d(n);
    if (!negative) {
        if (potential)
            *potential = std::move(d);
        return false;
    }
    std::partial_sum(begin.begin(), begin.end(), begin.begin());
    std::vector<Arc> arcs(edges.size());
    auto cursor = begin;
    for (const auto &e : edges)
        arcs[cursor[e.u]++] = {e.v, e.w};

    std::vector<int> roots(n), next, stack, order;
    std::iota(roots.begin(), roots.end(), 0);
    next.reserve(n);
    stack.reserve(n);
    order.reserve(n);
    std::vector<int> visited(n), queued(n);
    std::vector<unsigned char> active(n);
    int round = 0;
    const i64 lower_bound = -(i64(n) - 1) * negative;
    while (!roots.empty()) {
        ++round;
        order.clear();
        for (int root : roots) {
            if (visited[root] == round)
                continue;
            bool improves = false;
            for (int j = begin[root]; j < begin[root + 1]; ++j) {
                auto e = arcs[j];
                if (d[root] + e.w < d[e.v]) {
                    improves = true;
                    break;
                }
            }
            if (!improves)
                continue;
            stack.push_back(root);
            visited[root] = round;
            active[root] = 1;
            cursor[root] = begin[root];
            while (!stack.empty()) {
                int u = stack.back();
                if (cursor[u] == begin[u + 1]) {
                    order.push_back(u);
                    active[u] = 0;
                    stack.pop_back();
                    continue;
                }
                auto e = arcs[cursor[u]++];
                i64 candidate = d[u] + e.w;
                if (candidate >= d[e.v])
                    continue;
                // An active ancestor closes the actual DFS path. A strict
                // improvement makes this cycle negative; a zero cycle does
                // not improve the label and never triggers this check.
                if (active[e.v] || candidate < lower_bound)
                    return true;
                d[e.v] = candidate;
                if (visited[e.v] != round) {
                    visited[e.v] = round;
                    active[e.v] = 1;
                    cursor[e.v] = begin[e.v];
                    stack.push_back(e.v);
                }
            }
        }
        next.clear();
        for (auto it = order.rbegin(); it != order.rend(); ++it) {
            int u = *it;
            for (int j = begin[u]; j < begin[u + 1]; ++j) {
                auto e = arcs[j];
                i64 candidate = d[u] + e.w;
                if (candidate >= d[e.v])
                    continue;
                if (candidate < lower_bound)
                    return true;
                d[e.v] = candidate;
                if (queued[e.v] != round) {
                    queued[e.v] = round;
                    next.push_back(e.v);
                }
            }
        }
        roots.swap(next);
    }
    if (potential)
        *potential = std::move(d);
    return false;
}

void solve() {
    int N, M;
    cin >> N >> M;
    vector<Edge> E;
    for (auto i = 0; i < M; ++i) {
        int l, r, d;
        cin >> l >> r >> d;
        --l, --r;
        E.push_back({l, r, d});
        E.push_back({r, l, -d});
    }
    cout << (has_negative_cycle(N, E) ? "No\n" : "Yes\n");
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
