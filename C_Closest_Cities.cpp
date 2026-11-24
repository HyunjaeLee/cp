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
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    atcoder::fenwick_tree<int> ft1(N), ft2(N);
    for (auto i = 0; i < N - 1; ++i) {
        int w;
        if (i == 0 || A[i] - A[i - 1] > A[i + 1] - A[i]) {
            w = 1;
        } else {
            w = A[i + 1] - A[i];
        }
        ft1.add(i, w);
    }
    for (auto i = N - 1; 0 < i; --i) {
        int w;
        if (i == N - 1 || A[i] - A[i - 1] < A[i + 1] - A[i]) {
            w = 1;
        } else {
            w = A[i] - A[i - 1];
        }
        ft2.add(i, w);
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        if (x < y) {
            auto ans = ft1.sum(x, y);
            cout << ans << "\n";
        } else {
            auto ans = ft2.sum(y + 1, x + 1);
            cout << ans << "\n";
        }
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
