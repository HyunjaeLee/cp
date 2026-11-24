#define NDEBUG
#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint;

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
    int N, M, K, P;
    cin >> N >> M >> K >> P;
    Z::set_mod(P);
    Z C[111][111];
    Z dp[111][111][111];
    for (auto i = 0; i <= N; ++i) {
        C[i][0] = 1;
    }
    for (auto i = 1; i <= N; ++i) {
        for (auto j = 1; j <= N; ++j) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    vector<Z> f(N + 1);
    f[0] = 1;
    for (auto i = 1; i <= N; ++i) {
        f[i] = f[i - 1] * i;
    }
    for (auto n = 0; n <= N; ++n) {
        for (auto m = M; 1 <= m; --m) {
            for (auto k = 0; k <= min(K, n); ++k) {
                if (n == 0) {
                    dp[n][m][k] = 1;
                } else if (M == m) {
                    dp[n][m][k] = k == 1 ? f[n] : 0;
                } else {
                    for (auto i = 0; i < n; ++i) {
                        auto l = i, r = n - i - 1;
                        Z sum = 0;
                        for (auto s = 0; s <= min(k, i); ++s) {
                            sum += dp[l][m + 1][s] * dp[r][m + 1][k - s];
                        }
                        dp[n][m][k] += sum * C[n - 1][i];
                    }
                }
            }
        }
    }
    auto ans = dp[N][1][K];
    cout << ans.val() << "\n";
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
