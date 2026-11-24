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

map<i64, i128> dp;

#define TC
void solve() {
    auto f = [&](this auto &&self, i64 n) -> i64 {
        if (n < 4)
            return array<int, 4>{0, 1, 3, 2}[n];
        auto p = __lg(n);
        return min(self(n - ((1LL << p) - 1) + 1) + p + 1, ((1LL << (p + 1)) - 1) - n + p + 1);
    };
    auto pred = [&](i64 n) {
        if (n < 4)
            return true;
        auto p = __lg(n);
        auto l = f(n - ((1LL << p) - 1) + 1) + p + 1;
        auto r = ((1LL << (p + 1)) - 1) - n + p + 1;
        return l < r;
    };
    auto F = [&](this auto &&self, i64 n) -> i128 {
        if (n < 0)
            return 0;
        if (n < 4)
            return array<int, 4>{0, 1, 4, 6}[n];
        if (dp.contains(n))
            return dp[n];
        auto p = __lg(n);
        auto l = 1LL << p;
        auto r = n + 1;
        auto it = ranges::partition_point(views::iota(l, r), pred);
        auto m = *it;
        i128 sum = i128(((1LL << (p + 1)) - 1) + p + 1) * (r - m);
        sum -= i128(m + r - 1) * (r - m) / 2;
        sum += self(l - 1) + self((m - 1) - ((1LL << p) - 1) + 1) - 1 + i128(m - l) * (p + 1);
        return dp[n] = sum;
    };
    i64 L, R;
    cin >> L >> R;
    cout << i64((F(R) - F(L - 1)) % 998244353) << "\n";
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
