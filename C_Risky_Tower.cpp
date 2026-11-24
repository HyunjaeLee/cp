#include <atcoder/fenwicktree>
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
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

i64 op(i64 a, i64 b) { return a + b; }

i64 e() { return 0; }

#define TC
void solve() {
    int N, M;
    cin >> N >> M;
    vector<int> V(N);
    read(V);
    vector<vector<int>> A(N, vector<int>(M));
    for (auto &r : A) {
        read(r);
    }
    vector<array<int, 3>> X;
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            X.push_back({A[i][j], i, j});
        }
    }
    ranges::sort(X | views::reverse);
    vector<vector<int>> I(A);
    for (auto id = 0; id < N * M; ++id) {
        auto [x, i, j] = X[id];
        I[i][j] = id;
    }
    atcoder::segtree<i64, op, e> seg(N * M);
    atcoder::fenwick_tree<int> ft(N * M);
    auto ans = M;
    for (auto i = N - 1; 0 <= i; --i) {
        for (auto j = 0; j < M; ++j) {
            auto id = I[i][j];
            seg.set(id, A[i][j]);
            ft.add(id, 1);
        }
        auto r = seg.max_right(0, [&](auto x) { return x < V[i]; });
        if (r < N * M) {
            ans = min(ans, ft.sum(0, r + 1));
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
