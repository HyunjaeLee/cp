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
    if (1 < popcount(u32(N)) || (N == 2 && 0 < X)) {
        cout << "-1\n";
        return;
    }
    vector<vector<int>> A(N, vector<int>(N));
    if (X == 0) {
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < N; ++j) {
                A[i][j] = i ^ j;
            }
        }
    } else {
        vector<bool> used(N);
        vector<int> v;
        for (auto i = 0; i < N; ++i) {
            if (used[i])
                continue;
            used[i] = true;
            used[i ^ X] = true;
            v.emplace_back(i);
            v.emplace_back(i ^ X);
        }
        vector<int> a(N);
        auto p = 0, q = N / 2;
        for (auto i = 0; i < N / 2; ++i) {
            a[2 * i] = v[p++];
            a[2 * i + 1] = v[q++];
        }
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < N; ++j) {
                A[i][j] = a[i] ^ a[j];
                if ((i & 1) && (j & 1)) {
                    A[i][j] ^= X;
                }
            }
        }
    }
    for (const auto &row : A) {
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
