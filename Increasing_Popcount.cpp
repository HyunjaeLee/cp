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

#define TC
void solve() {
    vector<vector<i64>> C(61, vector<i64>(61));
    for (auto i = 0; i <= 60; ++i) {
        C[i][0] = 1;
    }
    for (auto i = 1; i <= 60; ++i) {
        for (auto j = 1; j <= 60; ++j) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    i64 L, R;
    cin >> L >> R;
    ++R;
    vector<i64> dp(61);
    while (L < R) {
        auto k = 0;
        while (L % (1LL << (k + 1)) == 0 && L + (1LL << (k + 1)) <= R) {
            ++k;
        }
        for (auto i = 0; i <= k; ++i) {
            dp[popcount(u64(L)) + i] += C[k][i];
        }
        for (auto i = 60; 0 < i; --i) {
            dp[i - 1] = max(dp[i - 1], dp[i]);
        }
        L += (1LL << k);
    }
    cout << dp[0] << "\n";
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
