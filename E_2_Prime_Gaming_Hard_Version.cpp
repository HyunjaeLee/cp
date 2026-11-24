#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint1000000007;

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

#define TC
void solve() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> good(N);
    for (auto i = 0; i < K; ++i) {
        int c;
        cin >> c;
        --c;
        good[c] = 1;
    }
    vector<vector<int>> dp(N + 1, vector<int>(1 << N, -1));
    constexpr auto inf = numeric_limits<int>::max() / 2;
    auto f = [&](this auto &&self, int n, int s) -> int {
        if (n == 1)
            return s & 1;
        auto &ret = dp[n][s];
        if (~ret)
            return ret;
        ret = (n & 1) == (N & 1) ? -inf : inf;
        for (auto i = 0; i < n; ++i) {
            if (!good[i])
                continue;
            auto t = (s & ((1 << i) - 1)) | ((s >> (i + 1)) << i);
            if ((n & 1) == (N & 1))
                ret = max(ret, self(n - 1, t));
            else
                ret = min(ret, self(n - 1, t));
        }
        return ret;
    };
    vector<Z> g(N + 1);
    for (auto a = 0; a <= N; ++a) {
        for (auto x = 1; x <= M; ++x) {
            g[a] += Z(M - x + 1).pow(a) * Z(x - 1).pow(N - a);
        }
    }
    Z ans = 0;
    for (auto s = 0; s < (1 << N); ++s) {
        if (f(N, s) == 0)
            continue;
        ans += g[popcount(u32(s))];
    }
    println("{}", ans.val());
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
