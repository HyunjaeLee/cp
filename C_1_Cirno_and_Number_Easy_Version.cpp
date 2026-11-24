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
    constexpr auto inf = numeric_limits<i64>::max() / 2;
    i64 ans = inf;
    auto f = [&](int i) {
        auto x = a;
        for (auto k = 0; k < i; ++k) {
            x /= 10;
        }
        return x % 10;
    };
    {
        auto fit = true;
        i64 x = 0;
        auto start = false;
        for (auto i = 19; 0 <= i; --i) {
            if (fit) {
                auto it = ranges::upper_bound(d, f(i));
                if (start && it == d.begin()) {
                    x = -1;
                    break;
                }
                auto v = it == d.begin() ? 0 : *prev(it);
                if (v < f(i)) {
                    fit = false;
                }
                if (0 < v) {
                    start = true;
                }
                x = x * 10 + v;
            } else {
                x = x * 10 + d[n - 1];
            }
        }
        if (0 <= x) {
            assert(x <= a);
            ans = min(ans, a - x);
        }
    }
    auto w = (a == 0 ? 1 : 0);
    for (auto x = a; x; x /= 10) {
        w++;
    }
    {
        auto fit = true;
        i64 x = 0;
        for (auto i = w; 0 <= i; --i) {
            if (fit) {
                auto it = ranges::lower_bound(d, f(i));
                if (it == d.end()) {
                    x = -1;
                    break;
                }
                auto v = *it;
                if (f(i) < v) {
                    fit = false;
                }
                x = x * 10 + v;
            } else {
                x = x * 10 + d[0];
            }
        }
        if (0 <= x) {
            assert(a <= x);
            ans = min(ans, x - a);
        }
    }
    {
        auto fit = true;
        i64 x = 0;
        for (auto i = w - 1; 0 <= i; --i) {
            if (fit) {
                auto it = ranges::lower_bound(d, f(i));
                if (it == d.end()) {
                    x = -1;
                    break;
                }
                auto v = *it;
                if (f(i) < v) {
                    fit = false;
                }
                x = x * 10 + v;
            } else {
                x = x * 10 + d[0];
            }
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
