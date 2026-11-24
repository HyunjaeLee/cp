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
    vector<int> A(N);
    read(A);
    vector<int> B(N);
    read(B);
    auto S = int(sqrt(2 * N)) + 1;
    i64 ans = 0;
    for (auto x = 1; x <= S; ++x) {
        vector<int> f(N + 1);
        for (auto i = 0; i < N; ++i) {
            auto p = A[i] * x - B[i];
            if (1 <= p && p <= N) {
                ans += f[p];
            }
            if (A[i] == x) {
                f[B[i]]++;
            }
        }
    }
    for (auto x = 1; x <= S; ++x) {
        vector<int> f(N + 1);
        for (auto i = N - 1; 0 <= i; --i) {
            auto p = A[i] * x - B[i];
            if (1 <= p && p <= N) {
                ans += f[p];
            }
            if (A[i] == x) {
                f[B[i]]++;
            }
        }
    }
    for (auto x = 1; x <= S; ++x) {
        vector<int> f(N + 1);
        for (auto i = 0; i < N; ++i) {
            if (A[i] <= S) {
                auto p = A[i] * x - B[i];
                if (1 <= p && p <= N) {
                    ans -= f[p];
                }
            }
            if (A[i] == x) {
                f[B[i]]++;
            }
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
