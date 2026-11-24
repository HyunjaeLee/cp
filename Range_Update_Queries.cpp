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

#include <atcoder/fenwicktree>

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<i64> A(N);
    read(A);
    for (auto i = N - 2; 0 <= i; --i) {
        A[i + 1] -= A[i];
    }
    atcoder::fenwick_tree<i64> ft(N + 1);
    for (auto i = 0; i < N; ++i) {
        ft.add(i, A[i]);
    }
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            ft.add(l, x);
            ft.add(r, -x);
        } else {
            int i;
            cin >> i;
            cout << ft.sum(0, i) << "\n";
        }
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
