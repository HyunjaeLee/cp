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

i64 dp[101][101][10101];

void solve() {
    memset(dp, -1, sizeof dp);
    int N, M;
    cin >> N >> M;
    vector<array<int, 2>> A(N);
    for (auto &[c, v] : A) {
        cin >> c >> v;
    }
    ranges::sort(A);
    constexpr auto inf = numeric_limits<i64>::max() / 2;
    auto f = [&](this auto &&self, int i, int k, int s) -> i64 {
        if (s < 0)
            return -inf;
        if (k == 0)
            return 0;
        auto &ret = dp[i][k][s];
        if (~ret)
            return ret;
        if (i == N - 1) {
            if (k == 1) {
                ret = A[i][1];
            } else {
                ret = -inf;
            }
        } else {
            auto d = A[i + 1][0] - A[i][0];
            ret = self(i + 1, k, s - k * d);
            ret = max(ret, A[i][1] + self(i + 1, k - 1, s - (k - 1) * d));
        }
        return ret;
    };
    for (auto j = 0; j <= M; ++j) {
        auto p = -1;
        i64 easy = 0;
        for (auto i = 0; i < N; ++i) {
            if (j < A[i][0]) {
                p = i;
                break;
            }
            easy += A[i][1];
        }
        if (p == -1) {
            cout << easy << "\n";
            continue;
        }
        auto d = A[p][0] - j;
        i64 ans = 0;
        for (auto k = 0; k <= N - p; ++k) {
            ans = max(ans, f(p, k, M - d * k));
        }
        ans += easy;
        cout << ans << "\n";
    }
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
