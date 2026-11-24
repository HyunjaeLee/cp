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

bool fuji(auto A) {
    auto N = int(size(A));
    auto i = 0;
    for (; i + 1 < N; ++i) {
        if (A[i] >= A[i + 1]) {
            break;
        }
    }
    for (; i + 1 < N; ++i) {
        if (A[i] <= A[i + 1]) {
            return false;
        }
    }
    return true;
}

int f[30][10];
i64 dp[30][10];

void init() {
    for (auto i = 0; i < 10; ++i) {
        f[0][i] = (2 * i) % 10;
        dp[0][i] = i;
    }
    for (auto i = 1; i < 30; ++i) {
        for (auto j = 0; j < 10; ++j) {
            f[i][j] = f[i - 1][f[i - 1][j]];
            dp[i][j] = dp[i - 1][j] + dp[i - 1][f[i - 1][j]];
        }
    }
}

i64 F(i64 x, int step) {
    assert(0 <= x && 0 <= step);
    if (step == 0)
        return x;
    auto u = x % 10;
    for (auto i = 0; i < 30; ++i) {
        if ((step >> i) & 1) {
            x += dp[i][u];
            u = f[i][u];
        }
    }
    return x;
}

#define TC
void solve() {
    int S, K;
    cin >> S >> K;
    i64 ans = 0;
    auto G = [&](int i) { return F(S, i) * (K - i); };
    for (auto i = 0; i < min(K, 10); ++i) {
        ans = max(ans, G(i));
    }
    if (10 <= K) {
        for (auto r = 0; r < 4; ++r) {
            auto pred = [&](int i) { return G(4 * i + r) < G(4 * (i + 1) + r); };
            auto it = ranges::partition_point(views::iota(0, K / 4), pred);
            ans = max(ans, G(4 * *it + r));
        }
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    init();
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
