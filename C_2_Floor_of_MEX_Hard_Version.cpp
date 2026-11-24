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

#include <atcoder/fenwicktree>
#include <atcoder/modint>

using Z = atcoder::modint1000000007;

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<int> F(N + 1);
    for (i64 i = 0; i < N; ++i) {
        auto l = (int)min<i64>(N, (i + 1) * A[i]);
        auto r = (int)min<i64>(N, (i + 1) * (A[i] + 1));
        F[l]++;
        F[r]--;
    }
    for (auto i = 0; i < N; ++i) {
        F[i + 1] += F[i];
    }
    for (auto i = 0; i < N; ++i) {
        F[i] = int(F[i] == 0);
    }
    vector<pair<int, int>> rng;
    for (i64 i = 0; i < N; ++i) {
        for (auto a = 0; a < A[i]; ++a) {
            auto l = (int)min<i64>(N, (i + 1) * a);
            auto r = (int)min<i64>(N, (i + 1) * (a + 1));
            rng.emplace_back(l, r);
        }
    }
    vector<int> R(N, N + 1);
    for (auto [l, r] : rng) {
        if (0 < l) {
            R[l - 1] = min(R[l - 1], r);
        }
    }
    for (auto i = N - 1; 0 < i; --i) {
        R[i - 1] = min(R[i - 1], R[i]);
    }
    atcoder::fenwick_tree<Z> dp(N + 1);
    dp.add(N, 1);
    for (auto i = N - 1; 0 <= i; --i) {
        if (F[i] == 0) {
            continue;
        }
        dp.add(i, dp.sum(i + 1, R[i]));
    }
    auto minr = N + 1;
    for (auto [l, r] : rng) {
        minr = min(minr, r);
    }
    Z ans = dp.sum(0, minr);
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
