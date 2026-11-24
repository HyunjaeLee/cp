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
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    read(A);
    auto x = A[0], y = A[1];
    ranges::sort(A);
    atcoder::fenwick_tree<int> ft(N);
    for (auto i = 0; i < N; ++i) {
        ft.add(i, 1);
    }
    for (auto i = 0; i < N; ++i) {
        if (ft.sum(i, i + 1) == 1 && A[i] == x) {
            ft.add(i, -1);
            break;
        }
    }
    for (auto i = 0; i < N; ++i) {
        if (ft.sum(i, i + 1) == 1 && A[i] == y) {
            ft.add(i, -1);
            break;
        }
    }
    auto ans = numeric_limits<int>::max();
    for (auto i = 0; i + M <= N; ++i) {
        if (ft.sum(i, i + M) == M) {
            auto a = max(0, x - A[i]);
            auto b = max(0, A[i + M - 1] - y);
            ans = min(ans, a + b);
        }
    }
    for (auto i = 0; i + M + 1 <= N; ++i) {
        if (ft.sum(i, i + M + 1) == M) {
            auto a = max(0, x - A[i]);
            auto b = max(0, A[i + M] - y);
            ans = min(ans, a + b);
        }
    }
    for (auto i = 0; i + M + 2 <= N; ++i) {
        if (ft.sum(i, i + M + 2) == M) {
            auto a = max(0, x - A[i]);
            auto b = max(0, A[i + M + 1] - y);
            ans = min(ans, a + b);
        }
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
