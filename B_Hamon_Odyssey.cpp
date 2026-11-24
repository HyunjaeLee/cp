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
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    auto acc = 0;
    vector<int> P;
    for (auto i = 0; i < N; ++i) {
        if (acc == 0) {
            acc = A[i];
        } else {
            acc &= A[i];
        }
        if (acc == 0) {
            P.push_back(i);
        }
    }
    acc = 0;
    auto ans = 1;
    auto cnt = 0;
    for (auto i = N - 1; 0 <= i; --i) {
        if (acc == 0) {
            acc = A[i];
        } else {
            acc &= A[i];
        }
        if (acc == 0) {
            cnt++;
            auto it = ranges::lower_bound(P, i);
            ans = max(ans, int(it - P.begin()) + cnt);
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
