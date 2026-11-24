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

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read<1>(A);
    vector<vector<int>> G(N);
    for (auto i = 0; i < N; ++i) {
        G[A[i]].push_back(i);
    }
    set<int> S;
    for (auto i = 0; i < N; ++i) {
        S.insert(i);
    }
    vector<int> ans(N, int(1e9));
    for (const auto &g : G) {
        for (auto i : g) {
            S.erase(i);
        }
        for (auto i : g) {
            auto it = S.lower_bound(i);
            if (it != S.end()) {
                auto j = *it;
                ans[i] = min(ans[i], j - i);
            }
            if (it != S.begin()) {
                auto j = *prev(it);
                ans[i] = min(ans[i], i - j);
            }
        }
        for (auto i : g) {
            S.insert(i);
        }
    }
    show(ans);
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
