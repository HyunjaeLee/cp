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
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<vector<i64>> dp(N + 1, vector<i64>(N + 1, -1));
    constexpr auto inf = numeric_limits<i64>::max() / 4;
    auto f = [&](this auto &&self, int i, int k) -> i64 {
        if (i == N - 1)
            return 0;
        auto &ret = dp[i][k];
        if (~ret)
            return ret;
        ret = inf;
        if (A[i] < A[i + 1]) {
            ret = min(ret, self(i + 1, k));
        }
        if (0 < k) {
            ret = min<i64>(ret, N - i - 1);
            for (auto j = i + 1; j < N; ++j) {
                if (A[i] < A[j]) {
                    ret = min(ret, j - i - 1 + self(j, k - 1));
                }
            }
        }
        return ret;
    };
    for (auto k = 1; k <= N; ++k) {
        i64 ans = f(0, k);
        for (auto i = 1; i < N; ++i) {
            ans = min(ans, i + f(i, k - 1));
        }
        cout << ans << " ";
    }
    cout << "\n";
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
