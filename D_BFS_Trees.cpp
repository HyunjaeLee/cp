#include <bits/stdc++.h>
using namespace std;
#define MOD 998244353

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
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> E(M);
    constexpr auto inf = numeric_limits<int>::max() / 2;
    vector<vector<int>> D(N, vector<int>(N, inf));
    for (auto &[u, v] : E) {
        cin >> u >> v;
        --u, --v;
        D[u][v] = D[v][u] = 1;
    }
    for (auto i = 0; i < N; ++i) {
        D[i][i] = 0;
    }
    for (auto k = 0; k < N; ++k) {
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < N; ++j) {
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }
    auto toposort = [&](const vector<vector<int>> &g) {
        vector<int> in(N);
        for (auto u = 0; u < N; ++u) {
            for (auto v : g[u]) {
                ++in[v];
            }
        }
        queue<int> q;
        for (auto i = 0; i < N; ++i) {
            if (in[i] == 0) {
                q.push(i);
            }
        }
        vector<int> order(N);
        for (auto i = 0; i < N; ++i) {
            auto u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (--in[v] == 0) {
                    q.push(v);
                }
            }
            order[N - 1 - i] = u;
        }
        return order;
    };
    vector<vector<i64>> A(N, vector<i64>(N));
    for (auto x = 0; x < N; ++x) {
        vector<vector<int>> g(N);
        vector<int> parent(N, -1);
        for (auto [u, v] : E) {
            if (D[x][u] + 1 == D[x][v]) {
                g[u].push_back(v);
                parent[v] = u;
            } else if (D[x][v] + 1 == D[x][u]) {
                g[v].push_back(u);
                parent[u] = v;
            }
        }
        auto order = toposort(g);
        for (auto y = x; y < N; ++y) {
            vector<int> dp(N);
            dp[y] = 1;
            for (auto u : order) {
                for (auto v : g[u]) {
                    dp[u] = min(2, dp[u] + dp[v]);
                }
            }
            if (dp[x] != 1) {
                continue;
            }
            vector<int> in(N);
            for (auto u = y; u != x; u = parent[u]) {
                ++in[u];
            }
            for (auto i = 0; i < M; ++i) {
                auto [u, v] = E[i];
                if ((D[x][u] - D[x][v]) * (D[y][u] - D[y][v]) == 1) {
                    if (D[x][u] + 1 == D[x][v]) {
                        ++in[v];
                    } else if (D[x][v] + 1 == D[x][u]) {
                        ++in[u];
                    }
                }
            }
            A[x][y] = 1;
            for (auto i = 0; i < N; ++i) {
                if (i != x) {
                    A[x][y] = A[x][y] * in[i] % MOD;
                }
            }
            A[y][x] = A[x][y];
        }
    }
    for (auto i = 0; i < N; ++i) {
        show(A[i]);
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
