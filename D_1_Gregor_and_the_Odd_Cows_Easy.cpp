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
    int N;
    cin >> N;
    vector<array<int, 2>> A(N);
    for (auto &[x, y] : A) {
        cin >> x >> y;
    }
    array<int, 4> freq{};
    for (auto [x, y] : A) {
        ++freq[x % 4 / 2 * 2 + y % 4 / 2];
    }
    auto comb = [&](i64 n, i64 k) -> i64 {
        if (0 <= k && k <= n) {
            i64 ret = 1;
            for (auto i = 0; i < k; ++i) {
                ret *= (n - i);
            }
            for (auto i = 0; i < k; ++i) {
                ret /= (k - i);
            }
            return ret;
        } else {
            return 0;
        }
    };
    i64 ans = 0;
    for (auto i = 0; i < 4; ++i) {
        for (auto j = i; j < 4; ++j) {
            for (auto k = j; k < 4; ++k) {
                array<int, 4> cnt{};
                cnt[i] += 1;
                cnt[j] += 1;
                cnt[k] += 1;
                auto x1 = i / 2 * 2;
                auto y1 = i % 2 * 2;
                auto x2 = j / 2 * 2;
                auto y2 = j % 2 * 2;
                auto x3 = k / 2 * 2;
                auto y3 = k % 2 * 2;
                auto dx1 = x2 - x1;
                auto dy1 = y2 - y1;
                auto dx2 = x3 - x2;
                auto dy2 = y3 - y2;
                auto dx3 = x1 - x3;
                auto dy3 = y1 - y3;
                auto g1 = gcd(dx1, dy1);
                auto g2 = gcd(dx2, dy2);
                auto g3 = gcd(dx3, dy3);
                if ((g1 + g2 + g3) % 4 == 0) {
                    i64 prod = 1;
                    for (auto s = 0; s < 4; ++s) {
                        prod *= comb(freq[s], cnt[s]);
                    }
                    ans += prod;
                }
            }
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
