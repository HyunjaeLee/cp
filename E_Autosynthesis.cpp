#include <bits/stdc++.h>
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
template <typename T> void read(vector<T> &a) { for (auto &x : a) cin >> x; }
template <typename T> void show(const vector<T> &a, string_view sep = " ", string_view end = "\n") {
    for (auto i = 0; i < int(a.size()); ++i) {
        if (i) cout << sep;
        cout << a[i];
    }
    cout << end;
}
// clang-format on

#include <cassert>
#include <vector>

#include <algorithm>
#include <utility>
#include <vector>

#include <algorithm>
#include <utility>
#include <vector>

namespace atcoder {
namespace internal {

template <class E> struct csr {
    std::vector<int> start;
    std::vector<E> elist;
    explicit csr(int n, const std::vector<std::pair<int, E>> &edges) : start(n + 1), elist(edges.size()) {
        for (auto e : edges) {
            start[e.first + 1]++;
        }
        for (int i = 1; i <= n; i++) {
            start[i] += start[i - 1];
        }
        auto counter = start;
        for (auto e : edges) {
            elist[counter[e.first]++] = e.second;
        }
    }
};

} // namespace internal

} // namespace atcoder

namespace atcoder {
namespace internal {

struct scc_graph {
public:
    explicit scc_graph(int n) : _n(n) {}

    int num_vertices() { return _n; }

    void add_edge(int from, int to) { edges.push_back({from, {to}}); }

    std::pair<int, std::vector<int>> scc_ids() {
        auto g = csr<edge>(_n, edges);
        int now_ord = 0, group_num = 0;
        std::vector<int> visited, low(_n), ord(_n, -1), ids(_n);
        visited.reserve(_n);
        auto dfs = [&](auto self, int v) -> void {
            low[v] = ord[v] = now_ord++;
            visited.push_back(v);
            for (int i = g.start[v]; i < g.start[v + 1]; i++) {
                auto to = g.elist[i].to;
                if (ord[to] == -1) {
                    self(self, to);
                    low[v] = std::min(low[v], low[to]);
                } else {
                    low[v] = std::min(low[v], ord[to]);
                }
            }
            if (low[v] == ord[v]) {
                while (true) {
                    int u = visited.back();
                    visited.pop_back();
                    ord[u] = _n;
                    ids[u] = group_num;
                    if (u == v)
                        break;
                }
                group_num++;
            }
        };
        for (int i = 0; i < _n; i++) {
            if (ord[i] == -1)
                dfs(dfs, i);
        }
        for (auto &x : ids) {
            x = group_num - 1 - x;
        }
        return {group_num, ids};
    }

    std::vector<std::vector<int>> scc() {
        auto ids = scc_ids();
        int group_num = ids.first;
        std::vector<int> counts(group_num);
        for (auto x : ids.second)
            counts[x]++;
        std::vector<std::vector<int>> groups(ids.first);
        for (int i = 0; i < group_num; i++) {
            groups[i].reserve(counts[i]);
        }
        for (int i = 0; i < _n; i++) {
            groups[ids.second[i]].push_back(i);
        }
        return groups;
    }

private:
    int _n;
    struct edge {
        int to;
    };
    std::vector<std::pair<int, edge>> edges;
};

} // namespace internal

} // namespace atcoder

namespace atcoder {

struct two_sat {
public:
    two_sat() : _n(0), scc(0) {}
    explicit two_sat(int n) : _n(n), _answer(n), scc(2 * n) {}

    void add_clause(int i, bool f, int j, bool g) {
        assert(0 <= i && i < _n);
        assert(0 <= j && j < _n);
        scc.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
        scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
    }
    bool satisfiable() {
        auto id = scc.scc_ids().second;
        for (int i = 0; i < _n; i++) {
            if (id[2 * i] == id[2 * i + 1])
                return false;
            _answer[i] = id[2 * i] < id[2 * i + 1];
        }
        return true;
    }
    std::vector<bool> answer() { return _answer; }

private:
    int _n;
    std::vector<bool> _answer;
    internal::scc_graph scc;
};

} // namespace atcoder

#line 27 "E_Autosynthesis.cpp"

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    for (auto i = 0; i < N; ++i) {
        --A[i];
    }
    atcoder::two_sat ts(6 * N);
    for (auto i = 0; i < N; ++i) {
        ts.add_clause(i, false, N + i, true);
        ts.add_clause(i, true, N + i, false);
    }
    vector<vector<int>> G(N);
    for (auto i = 0; i < N; ++i) {
        ts.add_clause(i, true, 2 * N + i, true);
        ts.add_clause(i, false, 2 * N + i, false);
        G[A[i]].push_back(2 * N + i);
    }
    auto timer = 3 * N;
    for (auto v : G) {
        vector<int> u;
        for (auto i = 0; i < N; ++i) {
            auto x = timer++;
            
        }
    }
    if (!ts.satisfiable()) {
        cout << "-1\n";
        return;
    }
    auto ans = ts.answer();
    for (auto i = 0; i < N; ++i) {
        println("x{}={} y{}={}", i + 1, ans[i], i + 1, ans[N + i]);
    }
    vector<int> B;
    for (auto i = 0; i < N; ++i) {
        if (!ans[i]) {
            B.push_back(A[i] + 1);
        }
    }
    cout << B.size() << "\n";
    show(B);
}

/// adfdjfladsjflkdjslfjadkfjlasdkfjlajdfkjfalk
int main() {
    // cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}