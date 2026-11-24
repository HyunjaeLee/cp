#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint998244353;

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

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<pair<int, int>> v(N);
    for (auto i = 0; i < N; ++i) {
        v[i] = {A[i], i % A[i]};
    }
    ranges::sort(v);
    v.erase(unique(begin(v), end(v)), end(v));
    auto V = int(v.size());
    vector<vector<int>> G(N);
    for (auto i = 0; i < V; ++i) {
        for (auto j = v[i].first + v[i].second; j < N; j += v[i].first) {
            G[j].push_back(i);
        }
    }
    vector<Z> F(V);
    vector<Z> dp(N);
    for (auto i = N - 1; 0 <= i; --i) {
        auto it = ranges::lower_bound(v, pair(A[i], i % A[i]));
        dp[i] = 1 + F[it - v.begin()];
        for (auto p : G[i]) {
            F[p] += dp[i];
        }
    }
    cout << dp[0].val() << "\n";
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
