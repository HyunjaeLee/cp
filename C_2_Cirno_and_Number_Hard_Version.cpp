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
    i64 a, n;
    cin >> a >> n;
    vector<int> d(n);
    read(d);
    if (a == 0) {
        cout << d[0] << "\n";
        return;
    }
    constexpr auto inf = numeric_limits<i64>::max() / 2;
    i64 ans = inf;
    auto f = [&](int i) {
        auto x = a;
        for (auto k = 0; k < i; ++k) {
            x /= 10;
        }
        return x % 10;
    };
    auto Pow = [&](int k) {
        i64 x = 1;
        for (auto i = 0; i < k; ++i) {
            x = x * 10;
        }
        return x;
    };
    {
        i64 dp[20][2][2]{};
        i8 vis[20][2][2]{};
        auto F = [&](this auto &&self, int pos, int start, int fit) -> i64 {
            if (pos == -1)
                return (0);
            auto &ret = dp[pos][start][fit];
            if (vis[pos][start][fit])
                return ret;
            vis[pos][start][fit] = true;
            ret = -inf;
            if (fit) {
                auto it = ranges::upper_bound(d, f(pos));
                if (start && it == d.begin()) {
                    return ret = -inf;
                }
                auto v = 0;
                if (it != d.begin())
                    v = *--it;
                ret = v * Pow(pos) + self(pos - 1, start || 0 < v, v == f(pos));
                if (ret < 0) {
                    if (start && it == d.begin()) {
                        return ret = -inf;
                    }
                    v = 0;
                    if (it != d.begin())
                        v = *--it;
                    ret = v * Pow(pos) + self(pos - 1, start || 0 < v, v == f(pos));
                }
            } else {
                ret = d[n - 1] * Pow(pos) + self(pos - 1, true, false);
            }
            return ret;
        };
        auto x = F(18, 0, 1);
        if (x == 0 && d[0] != 0) {
            x = -1;
        }
        if (0 <= x) {
            assert(x <= a);
            ans = min(ans, a - x);
        }
    }
    {
        i64 dp[20][2][2]{};
        i8 vis[20][2][2]{};
        auto F = [&](this auto &&self, int pos, int start, int fit) -> i64 {
            if (pos == -1)
                return (0);
            auto &ret = dp[pos][start][fit];
            if (vis[pos][start][fit])
                return ret;
            vis[pos][start][fit] = true;
            ret = -inf;
            if (fit) {
                auto it = ranges::lower_bound(d, f(pos));
                if (it == d.end()) {
                    return ret = -inf;
                }
                if (!start && f(pos) == 0) {
                    ret = self(pos - 1, false, true);
                }
                if (ret < 0) {
                    auto v = *it;
                    ret = v * Pow(pos) + self(pos - 1, true, v == f(pos));
                }
                if (ret < 0 && next(it) != d.end()) {
                    auto v = *next(it);
                    ret = v * Pow(pos) + self(pos - 1, true, v == f(pos));
                }
            } else {
                ret = d[0] * Pow(pos) + self(pos - 1, true, false);
            }
            return ret;
        };
        auto x = F(18, 0, 1);
        if (x == 0 && d[0] != 0) {
            x = -1;
        }
        if (0 <= x) {
            assert(a <= x);
            ans = min(ans, x - a);
        }
    }
    cout << ans << "\n";
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
