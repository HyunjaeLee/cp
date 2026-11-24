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
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    read(A);
    auto f = [&](int x) {
        i64 sum = 0;
        for (auto i = 0; i < N; ++i) {
            if (x <= A[i]) {
                sum += x;
            } else {
                sum += max(A[i], x - K);
            }
        }
        return sum;
    };
    i64 S = ranges::fold_left(A, 0LL, plus());
    auto pred = [&](int x) { return f(x) < S; };
    auto X = *ranges::partition_point(views::iota(1, ranges::max(A) + 1), pred);
    auto g = [&](int x) {
        i64 sum = 0;
        for (auto i = 0; i < N; ++i) {
            if (x <= A[i]) {
                sum += i64(x) * (x + 1) / 2;
            } else {
                sum += i64(A[i]) * (A[i] + 1) / 2;
                i64 cnt = max(A[i], x - K) - A[i];
                sum += cnt * ((A[i] + 1 + K) + (A[i] + cnt + K)) / 2;
            }
        }
        return sum;
    };
    i64 ans = g(X - 1) + (S - f(X - 1)) * X;
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
