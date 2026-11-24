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

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<i64> P(N + 1);
    for (auto i = 0; i < N; ++i) {
        P[i + 1] = P[i] + A[i];
    }
    auto query = [&](int l, int r) {
        assert(0 <= l && l <= r && r <= N);
        return P[r] - P[l];
    };
    auto ans = query(0, N);
    for (auto i = 2; i < N; ++i) {
        auto f = [&](int p) { return max({query(0, p + 1) + query(i, N), query(0, i), query(p + 1, N)}); };
        auto pred = [&](int p) { return f(p) > f(p + 1); };
        auto it = ranges::partition_point(views::iota(0, i - 2), pred);
        ans = min(ans, f(*it));
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
