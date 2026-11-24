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

#include <atcoder/dsu>
#include <atcoder/modint>
using Z = atcoder::modint998244353;

#define TC
void solve() {
    int N, M;
    cin >> N >> M;
    atcoder::dsu dsu(N);
    vector<vector<int>> adj(N);
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        dsu.merge(u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<Z> A(N - 1);
    auto K = int(dsu.groups().size());
    Z P = 1;
    for (auto i = 0; i < N; ++i) {
        if (dsu.leader(i) == i) {
            P *= dsu.size(i);
        }
    }
    if (dsu.leader(N - 1) == dsu.leader(N - 2)) {
        vector<int> parent(N, -1);
        [&](this auto &&self, int u) -> void {
            for (auto v : adj[u]) {
                if (v != parent[u]) {
                    parent[v] = u;
                    self(v);
                }
            }
        }(N - 2);
        A[parent[N - 1]] = K == 1 ? 1 : Z(N).pow(K - 2) * P;
    } else {
        vector<int> sz(N, 1);
        [&](this auto &&self, int u, int p) -> void {
            for (auto v : adj[u]) {
                if (v != p) {
                    self(v, u);
                    sz[u] += sz[v];
                }
            }
        }(N - 1, -1);
        for (auto u : adj[N - 1]) {
            A[u] = Z(N).pow(K - 2) * P * sz[u] / sz[N - 1];
        }
        [&](this auto &&self, int u, int p) -> void {
            A[u] = K == 2 ? 1
                          : Z(N).pow(K - 3) * P / Z(dsu.size(N - 1)) / Z(dsu.size(N - 2)) *
                                Z(dsu.size(N - 1) + dsu.size(N - 2));
            for (auto v : adj[u]) {
                if (v != p) {
                    self(v, u);
                }
            }
        }(N - 2, -1);
        for (auto i = 0; i < N; ++i) {
            if (dsu.leader(i) == dsu.leader(N - 1) || dsu.leader(i) == dsu.leader(N - 2))
                continue;
            A[i] = K == 2 ? 1 : Z(N).pow(K - 3) * P / Z(dsu.size(N - 1));
        }
    }
    show(A | views::transform([](Z x) { return x.val(); }));
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
