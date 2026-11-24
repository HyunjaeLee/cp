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
    i64 S, Q;
    cin >> S >> Q;
    vector<array<i64, 3>> blk;
    vector<i64> D;
    for (i64 i = 1; i * i <= S; ++i) {
        if (S % i == 0) {
            D.push_back(i);
            if (i * i < S) {
                D.push_back(S / i);
            }
        }
    }
    D.push_back(0);
    ranges::sort(D);
    for (auto [l, r] : D | views::pairwise) {
        blk.push_back({l, r, S / r});
    }
    auto B = int(blk.size());
    atcoder::fenwick_tree<i64> ft(B);
    for (auto i = 0; i < B; ++i) {
        auto [l, r, h] = blk[i];
        ft.add(i, h * (r - l));
    }
    auto query = [&](i64 x, i64 y) {
        auto L = *ranges::partition_point(views::iota(0, B), [&](int i) {
            auto [l, r, h] = blk[i];
            return h > y;
        });
        auto R = *ranges::partition_point(views::iota(0, B), [&](int i) {
            auto [l, r, h] = blk[i];
            return l <= x;
        }) - 1;
        if (L > R) {
            return x * y;
        }
        auto s1 = blk[L][0] * y;
        auto s2 = ft.sum(L, R);
        auto s3 = (x - blk[R][0]) * blk[R][2];
        return s1 + s2 + s3;
    };
    while (Q--) {
        i64 x, y;
        cin >> x >> y;
        cout << query(x, y) << "\n";
    }
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
