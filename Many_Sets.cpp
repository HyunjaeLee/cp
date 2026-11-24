#include <bits/stdc++.h>
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

#include <atcoder/modint>
using Z = atcoder::modint998244353;

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> A(N, vector<int>(M));
    for (auto i = 0; i < N; ++i) {
        read(A[i]);
    }
    vector<vector<int>> F(N * M, vector<int>(N));
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            F[A[i][j] - 1][i]++;
        }
    }
    Z ans = 0;
    vector<Z> P(N);
    P[0] = 1;
    for (auto i = 1; i < N; ++i) {
        P[i] = P[i - 1] * M;
    }
    for (auto x = 0; x < N * M; ++x) {
        Z pref = 1;
        for (auto i = 0; i < N; ++i) {
            ans += pref * F[x][i] * P[N - i - 1];
            pref *= M - F[x][i];
        }
    }
    cout << ans.val();
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
