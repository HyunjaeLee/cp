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

#include <atcoder/segtree>

int op(int a, int b) { return max(a, b); }
int e() { return 0; }

void solve() {
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    read<1>(A);
    read<1>(B);
    vector<int> I(N);
    ranges::iota(I, 0);
    auto ans = 0;
    {
        ranges::sort(I, {}, [&](int i) { return A[i]; });
        atcoder::segtree<int, op, e> seg(N);
        auto dp = 0;
        for (auto i : I) {
            dp = max(dp, seg.prod(0, B[i]) + 1);
            seg.set(B[i], seg.prod(0, B[i]) + 1);
        }
        ans = max(ans, dp);
    }
    {
        ranges::sort(I, {}, [&](int i) { return B[i]; });
        atcoder::segtree<int, op, e> seg(N);
        auto dp = 0;
        for (auto i : I) {
            dp = max(dp, seg.prod(0, A[i]) + 1);
            seg.set(A[i], seg.prod(0, A[i]) + 1);
        }
        ans = max(ans, dp);
    }
    ans += N;
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
