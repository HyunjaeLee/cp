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

#define TC
void solve() {
    int N, M;
    cin >> N >> M;
    atcoder::fenwick_tree<int> ft(M);
    for (auto i =0 ; i < M; ++i) ft.add(i, 1);
    auto a = 0, b = 0, c = 0;
    vector<int> X;
    for (auto i = 0; i < N; ++i) {
        int x;
        cin >> x;
        if (x == -1) {
            a += 1;
        } else if (x == -2) {
            b += 1;
        } else {
            --x;
            if (ft.sum(x, x + 1) == 1) {
                ft.add(x, -1);
                c += 1;
                X.push_back(x);
            }
        }
    }
    auto ans = c + max(min(ft.sum(0, M), a), min(ft.sum(0, M), b));
    for (auto x : X) {
        auto val = c + min(a, ft.sum(0, x)) + min(b, ft.sum(x + 1, M));
        ans = max(ans, val);
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
