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

void solve() {
    int N;
    cin >> N;
    vector<double> A(N);
    read(A);
    auto M = ranges::max(A);
    vector<double> B(N);
    for (auto i = 0; i < N; ++i) {
        B[i] = A[i] / M;
    }
    for (auto k = 1; k <= 10000; ++k) {
        vector<i64> C(N);
        for (auto i = 0; i < N; ++i) {
            C[i] = (i64)round(B[i] * k);
        }
        double sum = 0;
        for (auto i = 0; i < N; ++i) {
            sum += double(C[i]) * double(C[i]);
        }
        vector<double> D(N);
        auto d = sqrt(sum);
        for (auto i = 0; i < N; ++i) {
            D[i] = double(C[i]) / d;
        }
        double delta = 0;
        for (auto i = 0; i < N; ++i) {
            delta = max(delta, abs(A[i] - D[i]));
        }
        if (delta < 1e-6) {
            show(C, "\n", "");
            return;
        }
    }
    assert(0);
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
