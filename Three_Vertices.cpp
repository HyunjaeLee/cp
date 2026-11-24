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

void solve() {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<int> A(N);
    {
        string S;
        cin >> S;
        for (auto i = 0; i < N; ++i) {
            A[i] = S[i] - '0';
        }
    }
    vector<pair<int, int>> E(M);
    vector<vector<int>> G(N);
    for (auto &[u, v] : E) {
        cin >> u >> v;
        --u, --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    atcoder::dsu dsu(N);
    for (auto u = 0; u < N; ++u) {
        if (G[u].size() >= 3) {
            for (auto v : G[u]) {
                dsu.merge(v, G[u][0]);
            }
        }
    }
    for (auto [u, v] : E) {
        if (2 <= G[u].size() && 2 <= G[v].size()) {
            auto x = G[u][0] == v ? G[u][1] : G[u][0];
            auto y = G[v][0] == u ? G[v][1] : G[v][0];
            dsu.merge(x, y);
        }
    }
    vector<int> L;
    for (auto i = 0; i < N; ++i) {
        if (i == dsu.leader(i)) {
            L.push_back(i);
        }
    }
    ranges::sort(L);
    vector<int> ID(N);
    for (auto i = 0; i < N; ++i) {
        auto it = ranges::lower_bound(L, dsu.leader(i));
        ID[i] = int(it - L.begin());
    }
    vector<int> F(size(L));
    for (auto i = 0; i < N; ++i) {
        if (A[i]) {
            F[ID[i]] ^= 1;
        }
    }
    auto dom = -1;
    for (auto i = 0; i < N; ++i) {
        if (2 <= size(G[i])) {
            auto x = G[i][0];
            auto y = i;
            auto z = G[i][1];
            if (dsu.leader(x) == dsu.leader(y)) {
                dom = ID[dsu.leader(x)];
            } else if (dsu.leader(x) == dsu.leader(z)) {
                dom = ID[dsu.leader(x)];
            } else if (dsu.leader(y) == dsu.leader(z)) {
                dom = ID[dsu.leader(y)];
            }
            break;
        }
    }
    assert(1 <= size(L) && size(L) <= 3);
    while (Q--) {
        int x;
        cin >> x;
        --x;
        F[ID[x]] ^= 1;
        if (size(L) == 1) {
            cout << "Yes\n";
        } else if (size(L) == 2) {
            assert(dom != -1);
            auto ok = F[dom] == 0;
            cout << (ok ? "Yes\n" : "No\n");
        } else {
            if (F[2]) {
                F[0] ^= 1;
                F[1] ^= 1;
                F[2] ^= 1;
            }
            auto ok = F == vector{0, 0, 0};
            cout << (ok ? "Yes\n" : "No\n");
        }
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
