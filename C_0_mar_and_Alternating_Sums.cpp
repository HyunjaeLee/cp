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

#include <atcoder/modint>
using Z = atcoder::modint1000000007;

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<Z> dp1(N + 1);
    dp1[N] = 1;
    map<int, Z> mp1;
    for (auto i = N - 1; 0 <= i; --i) {
        dp1[i] = dp1[i + 1];
        dp1[i] += mp1[A[i]];
        mp1[A[i]] += dp1[i + 1];
    }
    vector<vector<Z>> dp2(N + 1, vector<Z>(2));
    dp2[N][1] = 1;
    map<int, Z> mp2, mp3, mp4;
    for (auto i = N - 1; 0 <= i; --i) {
        for (auto j = 0; j < 2; ++j) {
            dp2[i][j] = dp2[i + 1][j];
            dp2[i][j] += (j == 0 ? mp2 : mp3)[A[i]];
            if (j == 0) {
                dp2[i][j] += mp4[A[i] + 1];
            }
        }
        mp2[A[i]] += dp2[i + 1][0];
        mp3[A[i]] += dp2[i + 1][1];
        mp4[A[i]] += dp2[i + 1][1];
    }
    auto ans = dp1[0];
    for (auto i = 0; i < N; ++i) {
        if (A[i] == -1) {
            ans += dp2[i + 1][0];
        }
    }
    cout << ans.val() << "\n";
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
