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
using Z = atcoder::modint998244353;

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<int> rad(N + 1, 1);
    for (auto i = 2; i <= N; ++i) {
        if (1 < rad[i])
            continue;
        for (auto j = i; j <= N; j += i) {
            rad[j] *= i;
        }
    }
    vector<map<int, int>> dp(N + 1);
    auto f = [&](int x, int y) {
        auto it = dp[x].upper_bound(y);
        return prev(it)->second;
    };
    for (auto y = 1; y <= N; ++y) {
        dp[y][y] = y;
        for (auto x = rad[y]; x < y; x += rad[y]) {
            auto v = f(x - 1, y - 1);
            if (dp[x].empty() || dp[x].rbegin()->second != v) {
                dp[x][y] = v;
            }
        }
    }
    vector<Z> P(N + 1);
    P[0] = 1;
    for (auto i = 1; i <= N; ++i) {
        P[i] = P[i - 1] * 2;
    }
    ranges::sort(A);
    Z ans = 0;
    for (auto i = 0; i < N; ++i) {
        ans += f(A[i], A[i]);
        for (auto j = i + 1; j < N;) {
            auto it = dp[A[i]].upper_bound(A[j]);
            auto x = it == dp[A[i]].end() ? N + 1 : it->first;
            auto k = int(ranges::lower_bound(A, x) - A.begin());
            ans += f(A[i], A[j]) * P[j - i - 1] * (P[k - j] - 1);
            j = k;
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
