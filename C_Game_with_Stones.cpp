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
    int N;
    cin >> N;
    vector<i64> A(N);
    read(A);
    i64 ans = 0;
    for (auto i = 1; i < N; ++i) {
        A[i] -= A[i - 1];
    }
    array<map<i64, int>, 2> F;
    for (auto i = 0; i < N; ++i) {
        ++F[i & 1][0 <= i - 1 ? A[i - 1] : 0];
        for (auto it = F[i & 1].begin(); it != F[i & 1].end() && A[i] + it->first < 0;) {
            it = F[i & 1].erase(it);
        }
        for (auto it = F[(i & 1) ^ 1].end(); it != F[(i & 1) ^ 1].begin() && A[i] - prev(it)->first < 0;) {
            F[(i & 1) ^ 1].erase(prev(it));
        }
        ans += F[i & 1][-A[i]] + F[(i & 1) ^ 1][A[i]];
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
