#include <atcoder/segtree>
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

constexpr auto inf = numeric_limits<int>::max() / 2;

int op_min(int a, int b) { return min(a, b); }

int e_min() { return inf; }

int op_max(int a, int b) { return max(a, b); }

int e_max() { return -inf; }

#define TC
void solve() {
    int N;
    cin >> N;
    vector<pair<int, int>> P(N);
    vector<int> X, Y;
    for (auto &[x, y] : P) {
        cin >> x >> y;
        --x, --y;
        X.push_back(x);
        Y.push_back(y);
    }
    atcoder::segtree<int, op_min, e_min> seg_min(N);
    atcoder::segtree<int, op_max, e_max> seg_max(N);
    for (auto [x, y] : P) {
        seg_min.set(x, min(seg_min.get(x), y));
        seg_max.set(x, max(seg_max.get(x), y));
    }
    ranges::sort(X);
    X.erase(unique(X.begin(), X.end()), X.end());
    ranges::sort(Y);
    Y.erase(unique(Y.begin(), Y.end()), Y.end());
    i64 ans = 0;
    for (auto i = 1; i < int(X.size()); ++i) {
        auto l1 = seg_min.prod(0, X[i]);
        auto r1 = seg_max.prod(0, X[i]);
        auto l2 = seg_min.prod(X[i], N);
        auto r2 = seg_max.prod(X[i], N);
        auto l = max(l1, l2);
        auto r = min(r1, r2);
        auto s = ranges::lower_bound(Y, l);
        auto t = ranges::upper_bound(Y, r);
        ans += max<i64>(0, (t - s) - 1);
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
