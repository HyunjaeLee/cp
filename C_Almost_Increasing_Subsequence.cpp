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

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    read(A);
    atcoder::fenwick_tree<int> ft(N);
    for (auto i = 1; i < N - 1; ++i) {
        if (A[i - 1] >= A[i] && A[i] >= A[i + 1]) {
            ft.add(i, -1);
        }
    }
    while (Q--) {
        int l, r;
        cin >> l >> r;
        --l;
        auto ans = r - l;
        if (l + 1 < r - 1) {
            ans += ft.sum(l + 1, r - 1);
        }
        cout << ans << "\n";
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
