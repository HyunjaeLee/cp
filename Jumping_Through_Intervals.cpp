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
    vector<int> L(N), R(N);
    for (auto i = 0; i < N; ++i) {
        cin >> L[i] >> R[i];
    }
    vector<int> S(N), E(N);
    S[N - 1] = L[N - 1];
    E[N - 1] = R[N - 1];
    for (auto i = N - 2; 0 <= i; --i) {
        if (R[i] < S[i + 1]) {
            S[i] = E[i] = R[i];
        } else if (E[i + 1] < L[i]) {
            S[i] = E[i] = L[i];
        } else {
            S[i] = max(L[i], S[i + 1]);
            E[i] = min(R[i], E[i + 1]);
        }
    }
    vector<int> A(N);
    A[0] = S[0];
    for (auto i = 1; i < N; ++i) {
        A[i] = clamp(A[i - 1], L[i], E[i]);
    }
    show(A);
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
