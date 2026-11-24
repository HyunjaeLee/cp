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
    i64 N, W;
    cin >> N >> W;
    vector<vector<i64>> F(61);
    for (auto i = 0; i < N; ++i) {
        i64 X, Y;
        cin >> X >> Y;
        F[X].push_back(Y);
    }
    i64 ans = 0;
    for (auto i = 0; i < 60; ++i) {
        F[i].push_back(0);
        ranges::sort(F[i]);
        if ((W >> i) & 1) {
            ans += F[i].back();
            F[i].pop_back();
        }
        if (F[i].size() & 1) {
            F[i].insert(F[i].begin(), 0);
        }
        for (auto j = 0; j < int(F[i].size()); j += 2) {
            F[i + 1].push_back(F[i][j] + F[i][j + 1]);
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
