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

auto tree_diameter(const vector<vector<int>> &g) {
    assert(0 < g.size());
    auto n = int(g.size());
    std::vector<int> parent(n, -1);
    std::vector<int> depth(n);
    auto dfs = [&](int x) {
        std::vector<int> st;
        st.push_back(x);
        parent[x] = -1;
        depth[x] = 0;
        while (!st.empty()) {
            auto u = st.back();
            st.pop_back();
            for (auto v : g[u]) {
                if (v != parent[u]) {
                    st.push_back(v);
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
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
    vector<vector<int>> adj(N);
    for (auto i = 1; i < N; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto [d, path] = tree_diameter(adj);
    vector<int> color(N);
    for (auto x : path) {
        color[x] = 1;
    }
    for (auto i = 0; i < N; ++i) {
        if (color[i] == 0 && 1 < ssize(adj[i])) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
    vector<vector<int>> G(2 * N);
    for (auto i = 0; i <= d; ++i) {
        auto u = path[i];
        assert(color[u]);
        G[2 * i].push_back(u);
        for (auto v : adj[u]) {
            if (color[v] == 0) {
                G[2 * i + 1].push_back(v);
            }
        }
    }
    vector<int> ans;
    auto f = 0;
    for (auto i = 0; i <= d; ++i) {
        ans.insert(ans.end(), G[2 * i + f].begin(), G[2 * i + f].end());
        f ^= 1;
    }
    for (auto i = d; 0 <= i; --i) {
        ans.insert(ans.end(), G[2 * i + f].begin(), G[2 * i + f].end());
        f ^= 1;
    }
    show<1>(ans);
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
