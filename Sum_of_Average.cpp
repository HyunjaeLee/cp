#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint998244353;

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

// #define TC
void solve() {
    int N;
    cin >> N;
    vector<Z> P(N + 1);
    for (auto i = 1; i <= N; ++i) {
        int x;
        cin >> x;
        P[i] = x;
    }
    for (auto i = 1; i <= N; ++i) {
        P[i] += P[i - 1];
    }
    vector<Z> X(N + 1);
    for (auto i = 0; i < ceil_div(N, 2); ++i) {
        auto l = i, r = N - i;
        X[i + 1] = X[i] + P[r] - P[l];
    }
    for (auto i = ceil_div(N, 2) + 1; i <= N; ++i) {
        X[i] = X[N + 1 - i];
    }
    Z ans = 0;
    for (auto i = 1; i <= N; ++i) {
        ans += X[i] / i;
    }
    cout << ans.val();
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
