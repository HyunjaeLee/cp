#include <atcoder/segtree>
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

constexpr auto inf = numeric_limits<int>::max() / 2;
int op_min(int a, int b) { return min(a, b); }
int e_min() { return inf; }
int op_max(int a, int b) { return max(a, b); }
int e_max() { return -inf; }

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> X(N), Y(N), A(N), B(N);
    read(X);
    read(Y);
    read(A);
    read(B);
    atcoder::segtree<int, op_min, e_min> R(B);
    atcoder::segtree<int, op_max, e_max> L(B);
    vector<vector<vector<bool>>> used(2, vector<vector<bool>>(N, vector<bool>(N)));
    vector<array<int, 3>> ans;
    for (auto t = 0; t < 2 * N; ++t) {
        auto ok = false;
        for (auto i = 0; i < N; ++i) {
            for (auto j = i; j < N; ++j) {
                auto x = X[j - i];
                if (used[0][i][j] || R.prod(i, j + 1) < x) {
                    continue;
                }
                auto relaxed = false;
                for (auto k = i; k <= j; ++k) {
                    if (-inf < L.get(k) && L.get(k) <= x && x <= R.get(k)) {
                        relaxed = true;
                        ok = true;
                        L.set(k, -inf);
                    }
                }
                if (relaxed) {
                    ans.push_back({0, i, j});
                }
                used[0][i][j] = true;
            }
        }
        for (auto i = 0; i < N; ++i) {
            for (auto j = i; j < N; ++j) {
                auto y = Y[j - i];
                if (used[1][i][j] || y < L.prod(i, j + 1)) {
                    continue;
                }
                auto relaxed = false;
                for (auto k = i; k <= j; ++k) {
                    if (L.get(k) <= y && y <= R.get(k) && R.get(k) < inf) {
                        relaxed = true;
                        ok = true;
                        R.set(k, inf);
                    }
                }
                if (relaxed) {
                    ans.push_back({1, i, j});
                }
                used[1][i][j] = true;
            }
        }
        if (!ok) {
            break;
        }
    }
    for (auto i = 0; i < N; ++i) {
        if (A[i] < L.get(i) || R.get(i) < A[i]) {
            cout << "-1\n";
            return;
        }
    }
    cout << ans.size() << "\n";
    for (auto [op, l, r] : ans | views::reverse) {
        cout << (op ? "chmin " : "chmax ") << l + 1 << " " << r + 1 << "\n";
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
