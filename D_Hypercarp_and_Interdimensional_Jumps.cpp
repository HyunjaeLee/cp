#include <bits/stdc++.h>
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

#define TC
void solve() {
    i64 X, Y;
    cin >> X >> Y;
    i64 S = 0;
    i64 N = 0;
    while (S + (N + 1) <= X + Y) {
        N += 1;
        S += N;
    }
    auto a = floor_div(X + Y - S, 2LL);
    // auto b = ceil_div(X + Y - S, 2LL);
    auto want = X - a;
    string ans(N, 'Y');
    for (auto i = 0; i < N; ++i) {
        if ((N - i) <= want) {
            want -= (N - i);
            ans[i] = 'X';
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
