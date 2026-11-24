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
    string S;
    cin >> S;
    auto N = int(S.size());
    if (ranges::all_of(S, [](char c) { return c == '1'; })) {
        cout << i64(N) * N << "\n";
        return;
    }
    S += S;
    auto acc = 0;
    auto x = 0;
    for (auto i = 0; i < int(S.size()); ++i) {
        if (S[i] == '0') {
            acc = 0;
        } else {
            acc += 1;
        }
        x = max(x,acc);
    }
    auto ans = floor_div<i64>(x + 1, 2) * ceil_div<i64>(x + 1, 2);
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
