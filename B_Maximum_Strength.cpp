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
    string L, R;
    cin >> L >> R;
    ranges::reverse(L);
    L.resize(R.size(), '0');
    ranges::reverse(L);
    auto N = int(R.size());
    auto ans = 0;
    for (auto i = 0; i < N; ++i) {
        if (L[i] != R[i]) {
            ans = (N - i - 1) * 9 + abs(L[i] - R[i]);
            break;
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
