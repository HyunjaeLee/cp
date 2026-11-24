#include <atcoder/lazysegtree>
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

constexpr auto inf = numeric_limits<i64>::max() / 2;
using S = pair<i64, i64>;
S op(S a, S b) { return {min(a.first, b.first), max(a.second, b.second)}; }
S e() { return {inf, -inf}; }
using F = i64;
S mapping(F f, S x) { return {x.first + f, x.second + f}; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

void solve() {
    int N;
    cin >> N;
    vector<i64> A(N + 1);
    for (auto i = 1; i <= N; ++i) {
        cin >> A[i];
    }
    auto P = A;
    inclusive_scan(begin(P), end(P), begin(P));
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(N + 1);
    for (auto i = 0; i <= N; ++i) {
        seg.set(i, {P[i], P[i]});
    }
    auto ans = seg.all_prod().second - seg.all_prod().first + 1;
    for (auto i = 1; i <= N; ++i) {
        seg.apply(i, N + 1, -2 * A[i]);
        ans = max(ans, seg.all_prod().second - seg.all_prod().first + 1);
        seg.apply(i, N + 1, 2 * A[i]);
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
