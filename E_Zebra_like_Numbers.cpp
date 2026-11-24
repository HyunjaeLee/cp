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

// O(n^3), requires distinct positive integers including 1
// return (is canonical, smallest counterexample w, M(w))
// David Pearson, "A Polynomial-time Algorithm for the Change-Making Problem"
template <typename T> std::tuple<bool, T, std::vector<T>> greedy_optimality(std::vector<T> coins) {
    auto n = int(coins.size());
    std::sort(coins.rbegin(), coins.rend());
    auto greedy = [&](T x) {
        std::vector<T> v(n);
        for (auto i = 0; i < n; ++i) {
            v[i] = x / coins[i];
            x %= coins[i];
        }
        return v;
    };
    auto count = [](const std::vector<T> &v) { return std::accumulate(v.begin(), v.end(), T(0)); };
    auto comp = [&](const auto &a, const auto &b) {
        const auto &[ca, wa, ma] = a;
        const auto &[cb, wb, mb] = b;
        if (ca != cb)
            return ca < cb;
        if (wa != wb)
            return wa < wb;
        auto sa = count(ma);
        auto sb = count(mb);
        if (sa != sb)
            return sa < sb;
        return ma > mb;
    };
    std::tuple<bool, T, std::vector<T>> ans{true, -1, {}};
    for (auto i = 1; i < n; ++i) {
        auto v = greedy(coins[i - 1] - 1);
        for (auto j = i; j < n; ++j) {
            std::vector<T> mw(n);
            std::copy(v.begin(), v.begin() + j, mw.begin());
            mw[j] = v[j] + 1;
            auto w = std::inner_product(coins.begin(), coins.end(), mw.begin(), T(0));
            auto gw = greedy(w);
            if (count(mw) < count(gw)) {
                ans = std::ranges::min(ans, {false, w, mw}, comp);
            }
        }
    }
    return ans;
}

vector<i64> C{1};

map<pair<i64, i64> , i64> dp;

i64 F(i64 n, i64 k) {
    if (k < 0)
        return 0;
    if (n == 0)
        return k == 0 ? 1 : 0;
    if (dp.contains({n, k}))
        return dp[{n, k}];
    auto &ret = dp[{n, k}];
    auto c = *prev(ranges::upper_bound(C, n));
    for (i64 i = 0; i <= n; i += c) {
        auto m = min(i + c - 1, n);
        ret += F(m % c, k - m / c);
    }
    return ret;
}

#define TC
void solve() {
    i64 L, R, K;
    cin >> L >> R >> K;
    auto ans = F(R, K) - F(L - 1, K);
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    while (C.back() < 1'000'000'000'000'000'000LL) {
        C.push_back(4 * C.back() + 1);
    }
    auto [canonical, w, mw] = greedy_optimality(C);
    assert(canonical);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
