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

i128 isqrt(i128 x) {
    auto pred = [&](i128 s) { return s * s < x; };
    auto it = ranges::partition_point(views::iota(i128(0), i128(numeric_limits<i64>::max() / 2)), pred);
    return *it;
}

void solve() {
    i64 X;
    cin >> X;
    auto Y = abs(1 - 4 * X);
    vector<i64> D;
    for (i64 i = 1; i * i <= Y; ++i) {
        if (Y % i == 0) {
            D.push_back(i);
            if (i * i < Y) {
                D.push_back(Y / i);
            }
        }
    }
    set<i64> ans;
    auto F = [&](i64 a, i64 b) {
        if ((b - a) % 4 == 0) {
            auto k = i128(b - a) / 4;
            auto r = 1 - 4 * (X - k * k);
            if (0 <= r) {
                auto s = (i64)isqrt(r);
                ans.insert((-1 + s) / 2);
                ans.insert((-1 - s) / 2);
            }
        }
    };
    for (auto d : D) {
        auto a = d;
        auto b = Y / d;
        if (1 - 4 * X < 0) {
            F(a, -b);
            F(-a, b);
        } else {
            F(a, b);
            F(-a, -b);
        }
    }
    cout << size(ans) << "\n";
    show(ans);
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
