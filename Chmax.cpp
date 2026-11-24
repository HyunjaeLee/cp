#include <atcoder/segtree>
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

int op(int a, int b) { return max(a, b); }
int e() { return 0; }

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    for (auto &a : A)
        --a;
    auto pref = A;
    for (auto i = 0; i < N - 1; ++i) {
        pref[i + 1] = max(pref[i + 1], pref[i]);
    }
    vector<int> B;
    for (auto i = 1; i < N; ++i) {
        if (pref[i - 1] == pref[i]) {
            B.push_back(A[i]);
        }
    }
    auto M = int(B.size());
    auto ans = N - M;
    if (0 < M) {
        vector<int> dp(M);
        atcoder::segtree<int, op, e> seg(N);
        for (auto i = 0; i < M; ++i) {
            dp[i] = seg.prod(0, B[i]) + 1;
            seg.set(B[i], dp[i]);
        }
        ans += seg.all_prod();
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
