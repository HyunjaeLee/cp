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
    auto ok = N <= K && K < 2 * N;
    if (!ok) {
        cout << "-1\n";
        return;
    }
    auto e = K - N;
    auto l = 1, r = N * N;
    vector<vector<int>> A(N, vector<int>(N, -1));
    for (auto i = 0; i < N - e; ++i) {
        A[i][i] = l++;
    }
    for (auto i = N - e; i < N; ++i) {
        A[i][i] = r--;
        A[i][i - 1] = l++;
        A[i - 1][i] = l++;
    }
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            if (A[i][j] == -1) {
                A[i][j] = l++;
            }
        }
    }
    for (auto row : A) {
        show(row);
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
