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
    int N, X;
    cin >> N >> X;
    vector<i64> A(N);
    read(A);
    auto pred = [&](int k) -> bool {
        auto cnt = 0;
        i64 r = -k - 1;
        for (auto i = 0; i < N; ++i) {
            if (A[i] <= r + k || (i + 1 < N && A[i + 1] - A[i] <= k)) {
                r = A[i];
            } else {
                cnt++;
                r = A[i] + k;
            }
        }
        return cnt > X;
    };
    constexpr auto inf = numeric_limits<int>::max() / 2;
    auto it = ranges::partition_point(views::iota(1, inf), pred);
    cout << *it << "\n";
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
