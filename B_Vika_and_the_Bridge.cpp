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
    vector<int> A(N);
    read(A);
    vector<vector<int>> G(K, {0});
    for (auto i = 0; i < N; ++i) {
        G[A[i] - 1].push_back(i + 1);
    }
    for (auto i = 0; i < K; ++i) {
        G[i].push_back(N + 1);
    }
    auto pred = [&](int x) {
        for (const auto &v : G) {
            auto cnt = 0;
            auto ok = true;
            for (auto i = 0; i < int(v.size()) - 1; ++i) {
                if (v[i + 1] <= v[i] + x) {
                    // pass
                } else if (v[i + 1] <= v[i] + 2 * x) {
                    if (cnt++) {
                        ok = false;
                    }
                } else {
                    ok = false;
                }
            }
            if (ok) {
                return false;
            }
        }
        return true;
    };
    auto it = ranges::partition_point(views::iota(0, 2 * N), pred);
    cout << *it - 1 << "\n";
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
