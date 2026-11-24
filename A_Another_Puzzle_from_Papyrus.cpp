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
    int N, C;
    cin >> N >> C;
    vector<int> A(N), B(N);
    read(A);
    read(B);
    auto ok = true;
    i64 sum = 0;
    for (auto i = 0; i < N; ++i) {
        if (A[i] < B[i]) {
            ok = false;
            break;
        }
        sum += A[i] - B[i];
    }
    vector<int> P(N), Q(N);
    ranges::iota(P, 0);
    ranges::iota(Q, 0);
    ranges::sort(P, {}, [&](int i) { return A[i]; });
    ranges::sort(Q, {}, [&](int i) { return B[i]; });
    i64 ans = 0;
    for (auto i = 0; i < N; ++i) {
        if (A[P[i]] < B[Q[i]]) {
            cout << "-1\n";
            return;
        }
        ans += A[P[i]] - B[Q[i]];
        A[P[i]] = B[Q[i]];
    }
    if (A != B) {
        ans += C;
    }
    if (ok) {
        ans = min(ans, sum);
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
