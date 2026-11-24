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
    auto query = [](u32 x) {
        cout << x << endl;
        u32 r;
        cin >> r;
        return r;
    };
    auto xy = query(0); // x + y
    u32 n = 0b010101010101010101010101010101;
    auto xy0 = -(query(n) - 2 * n - xy); // (0101 & x) + (0101 & y)
    auto xy1 = xy - xy0;
    array<u32, 30> a{};
    for (auto i = 0; i < 30; ++i) {
        if (i & 1) {
            a[i] = (xy1 >> i) & 0b11;
        } else {
            a[i] = (xy0 >> i) & 0b11;
        }
    }
    cout << "!" << endl;
    u32 m;
    cin >> m;
    u32 ans = m + m + xy;
    for (auto i = 0; i < 30; ++i) {
        if ((m >> i) & 1) {
            ans -= a[i] << i;
        }
    }
    cout << ans << endl;
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
