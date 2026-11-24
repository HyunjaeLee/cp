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
    vector<int> A(N);
    vector<int> B(N);
    read(A);
    read(B);
    vector<vector<Z>> dp(N + 12, vector<Z>(2));
    constexpr auto inf = numeric_limits<int>::max() / 2;
    auto solve = [&](int i, int f) -> Z {
        Z ret = 0;
        array<int, 2> p{-inf, -inf};
        if (0 <= i - 1) {
            p = {A[i - 1], B[i - 1]};
        }
        if (f) {
            swap(p[0], p[1]);
        }
        array<int, 2> q{A[i], B[i]};
        if (p[0] <= q[0] && p[1] <= q[1]) {
            ret += dp[i + 1][0];
        }
        swap(q[0], q[1]);
        if (p[0] <= q[0] && p[1] <= q[1]) {
            ret += dp[i + 1][1];
        }
        return ret;
    };
    dp[N][0] = dp[N][1] = 1;
    for (auto i = N - 1; 0 <= i; --i) {
        dp[i][0] = solve(i, 0);
        dp[i][1] = solve(i, 1);
    }
    auto ans = dp[0][0].val();
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
