#include <atcoder/convolution>
#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint1000000007;

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

vector<Z> operator+(const vector<Z> &a, const vector<Z> &b) {
    assert(a.size() == b.size());
    vector<Z> c(a.size());
    for (auto i = 0; i < int(a.size()); ++i) {
        c[i] = a[i] + b[i];
    }
    return c;
}

vector<Z> operator-(const vector<Z> &a, const vector<Z> &b) {
    assert(a.size() == b.size());
    vector<Z> c(a.size());
    for (auto i = 0; i < int(a.size()); ++i) {
        c[i] = a[i] - b[i];
    }
    return c;
}

vector<Z> shift(vector<Z> a) {
    auto n = int(a.size());
    for (auto i = n - 1; 0 < i; --i) {
        a[i] = a[i - 1];
    }
    a[0] = 0;
    return a;
}

vector<vector<int>> rooted_tree(const vector<vector<int>> &adj, int root) {
    vector<vector<int>> g(adj.size());
    [&](this auto &&self, int u, int p) -> void {
        for (auto v : adj[u]) {
            if (v == p)
                continue;
            g[u].push_back(v);
            self(v, u);
        }
    }(root, -1);
    return g;
}

// https://judge.yosupo.jp/submission/87815
template <typename mint, atcoder::internal::is_modint_t<mint> * = nullptr>
std::vector<mint> arbitrary_mod_convolution(const std::vector<mint> &a, const std::vector<mint> &b) {
    int n = int(a.size()), m = int(b.size());
    if (n == 0 or m == 0)
        return {};

    static constexpr long long MOD1 = 754974721; // 2^24
    static constexpr long long MOD2 = 167772161; // 2^25
    static constexpr long long MOD3 = 469762049; // 2^26
    static constexpr long long M1M2 = MOD1 * MOD2;
    static constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(MOD1, MOD2).second;
    static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2, MOD3).second;

    std::vector<int> a2(n), b2(m);
    for (int i = 0; i < n; ++i)
        a2[i] = a[i].val();
    for (int i = 0; i < m; ++i)
        b2[i] = b[i].val();

    auto c1 = atcoder::convolution<MOD1>(a2, b2);
    auto c2 = atcoder::convolution<MOD2>(a2, b2);
    auto c3 = atcoder::convolution<MOD3>(a2, b2);

    std::vector<mint> c(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) {
        long long x1 = c1[i];
        long long x2 = (atcoder::static_modint<MOD2>(c2[i] - x1) * INV_M1_MOD2).val();
        long long x3 = (atcoder::static_modint<MOD3>(c3[i] - x1 - x2 * MOD1) * INV_M1M2_MOD3).val();
        c[i] = x1 + x2 * MOD1 + x3 * mint(M1M2).val();
    }
    return c;
}

void solve() {
    int N;
    cin >> N;
    vector<vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    adj = rooted_tree(adj, 0);
    vector<int> order;
    [&](this auto &&self, int u) -> void {
        for (auto v : adj[u]) {
            self(v);
        }
        order.push_back(u);
    }(0);
    vector<vector<vector<Z>>> dp(N, vector<vector<Z>>(3));
    auto conv = [&](const vector<Z> &a, const vector<Z> &b) { return arbitrary_mod_convolution(a, b); };
    for (auto u : order) {
        {
            dp[u][0] = {0, 1};
            for (auto v : adj[u]) {
                dp[u][0] = conv(dp[u][0], dp[v][0] + shift(dp[v][1]) + dp[v][2]);
            }
        }
        {
            dp[u][1] = {1, 0};
            for (auto v : adj[u]) {
                dp[u][1] = conv(dp[u][1], dp[v][1] + dp[v][2]);
            }
        }
        {
            vector<Z> a{0, 1};
            for (auto v : adj[u]) {
                a = conv(a, dp[v][0] + dp[v][1] + dp[v][2]);
            }
            vector<Z> b{0, 1};
            for (auto v : adj[u]) {
                b = conv(b, dp[v][1] + dp[v][2]);
            }
            dp[u][2] = a - b;
        }
    }
    auto ans = dp[0][0] + dp[0][1] + dp[0][2];
    for (auto i = 0; i <= N; ++i) {
        cout << ans[i].val() << "\n";
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
