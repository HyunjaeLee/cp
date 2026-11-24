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

#define TC
void solve() {
    int N, M;
    cin >> N >> M;
    vector<i64> A(N);
    read(A);
    vector<int> B(M);
    read(B);
    auto g = 0;
    for (auto x : B) {
        g = gcd(g, x);
    }
    vector<vector<i64>> F(g);
    for (auto i = 0; i < N; ++i) {
        F[i % g].push_back(A[i]);
    }
    for (auto &f : F) {
        ranges::sort(f);
    }
    i64 ans = numeric_limits<i64>::min();
    for (auto s = 0; s < 2; ++s) {
        i64 sum = 0;
        for (const auto &f : F) {
            auto k = int(f.size());
            atcoder::fenwick_tree<i64> ft(k);
            for (auto i = 0; i < k; ++i) {
                ft.add(i, f[i]);
            }
            i64 v = numeric_limits<i64>::min();
            for (auto i = s; i <= k; i += 2) {
                v = max(v, -ft.sum(0, i) + ft.sum(i, k));
            }
            sum += v;
        }
        ans = max(ans, sum);
    }
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
