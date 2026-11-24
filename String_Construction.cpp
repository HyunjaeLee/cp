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
template <typename T> void read(vector<T> &a) { for (auto &x : a) cin >> x; }
template <typename T> void show(const vector<T> &a, string_view sep = " ", string_view end = "\n") {
    for (auto i = 0; i < int(a.size()); ++i) {
        if (i) cout << sep;
        cout << a[i];
    }
    cout << end;
}
// clang-format on

#define TC
void solve() {
    int N, K;
    cin >> N >> K;
    if (N - 2 < K) {
        cout << "-1\n";
        return;
    }
    vector<int> A(N), B(N);
    for (auto i = 0; i < N; ++i) {
        A[i] = i & 1;
        B[i] = i;
    }
    for (auto i = 0; i < K; ++i) {
        auto j = N - 1 - i;
        if (A[j] == 0) {
            B[j] = 0;
        } else {
            B[j] = 1;
        }
    }
    vector<array<int, 2>> C(N);
    for (auto i = 0; i < N; ++i) {
        C[i] = {B[i], A[i]};
    }
    ranges::sort(C);
    for (auto i = 0; i < N; ++i) {
        cout << C[i][1];
    }
    cout << "\n";
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
