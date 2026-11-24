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

#include <atcoder/modint>
using Z = atcoder::modint998244353;

#define TC
void solve() {
    int N;
    cin >> N;
    string S;
    cin >> S;
    vector<vector<vector<Z>>> dp(N + 1, vector<vector<Z>>(2, vector<Z>(2)));
    dp[N][0][0] = dp[N][0][1] = dp[N][1][0] = dp[N][1][1] = 1;
    for (auto i = N - 1; 0 <= i; --i) {
        for (auto j = 0; j < 2; ++j) {
            for (auto k = 0; k < 2; ++k) {
                vector<char> can;
                if (S[i] == '0') {
                    can.push_back(0);
                } else if (S[i] == '1') {
                    can.push_back(1);
                } else {
                    can.push_back(0);
                    can.push_back(1);
                }
                for (auto x : can) {
                    if (i <= 1 || tuple(j, k, x) == tuple{0, 0, 1} || tuple(j, k, x) == tuple{1, 0, 0} || tuple(j, k, x) == tuple{0, 1, 1} || tuple(j, k, x) == tuple{1, 1, 0}) {
                        dp[i][j][k] += dp[i + 1][k][x];
                    }
                }
            }
        }
    }
    auto ans = dp[0][0][0];
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
