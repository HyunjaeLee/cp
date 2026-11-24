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
template <typename T> void read(vector<T> &a) { for (auto &x : a) cin >> x; }
template <typename T> void show(const vector<T> &a, string_view sep = " ", string_view end = "\n") {
    for (auto i = 0; i < int(a.size()); ++i) {
        if (i) cout << sep;
        cout << a[i];
    }
    cout << end;
}
// clang-format on

#define TC
void solve() {
    int N;
    string S, T;
    cin >> N >> S >> T;
    auto a = 0;
    for (auto i = 0; i < N; ++i) {
        if (S[i] != T[i]) {
            a++;
        }
    }
    ranges::reverse(T);
    auto b = 0;
    for (auto i = 0; i < N; ++i) {
        if (S[i] != T[i]) {
            b++;
        }
    }
    auto x = (a & 1) ? 2 * a - 1 : 2 * a;
    auto y = (b & 1) ? 2 * b : 2 * b - 1;
    x = max(0, x);
    y = max(2, y);
    auto ans = min(x, y);
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
