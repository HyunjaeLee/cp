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
    i64 N, M, K;
    cin >> N >> M >> K;
    constexpr i64 inf = i64(1e16);
    vector<pair<i64, i64>> rng(N);
    vector<i64> X;
    X.push_back(-1);
    X.push_back(inf);
    for (auto &[l, r] : rng) {
        cin >> l >> r;
        --l;
        X.push_back(l);
        X.push_back(r);
    }
    ranges::sort(X);
    X.erase(unique(begin(X), end(X)), end(X));
    auto I = [&](i64 x) {
        auto it = ranges::lower_bound(X, x);
        return it - begin(X);
    };
    vector<i64> P1(size(X));
    vector<i64> P2(size(X));
    for (auto [l, r] : rng) {
        auto il = I(l);
        auto ir = I(r);
        P1[il] -= l;
        P1[ir] += r;
        P2[il] -= 1;
        P2[ir] += 1;
    }
    for (auto i = 0; i < int(X.size()) - 1; ++i) {
        P1[i + 1] += P1[i];
        P2[i + 1] += P2[i];
    }
    auto prod = [&](i64 l, i64 r) {
        auto il = I(l);
        auto ir = I(r);
        return (P1[ir - 1] - P1[il - 1]) + P2[il - 1] * l + (P2.back() - P2[ir - 1]) * r;
    };
    if (K == 0) {
        cout << inf << "\n";
        return;
    }
    vector<i64> F(N);
    for (auto i = 0; i < N; ++i) {
        auto [l, r] = rng[i];
        F[i] = prod(l, l + M);
    }
    i64 L = -1, R = -1;
    for (auto i = 0; i < N; ++i) {
        if (K <= F[i]) {
            L = rng[i].first;
            R = rng[i].second;
        }
    }
    if (L == -1 && R == -1) {
        cout << "-1\n";
        return;
    }
    auto pred = [&](i64 p) { return K <= prod(p, p + M); };
    auto it = ranges::partition_point(views::iota(L, R), pred);
    auto s = *it - 1;
    assert(prod(s, s + M) == K);
    auto ans = s + 1;
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
