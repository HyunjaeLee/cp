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
    int L, R;
    cin >> L >> R;
    auto a = L, c = R;
    auto p = -1;
    for (auto i = 29; 0 <= i; --i) {
        if (((R >> i) & 1) > ((L >> i) & 1)) {
            p = i;
            break;
        }
    }
    auto b1 = (R >> p) << p;
    auto b2 = (L >> p) << p;
    for (auto i = p - 1; 0 <= i; --i) {
        if (((L >> i) & 1) != ((R >> i) & 1)) {
            b2 |= 1 << i;
        } else {
            b1 |= (((L >> i) & 1) ^ 1) << i;
            b2 |= (((L >> i) & 1) ^ 1) << i;
        }
    }
    auto b = a < b1 && b1 < c ? b1 : b2;
    cout << a << " " << b << " " << c << "\n";
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
