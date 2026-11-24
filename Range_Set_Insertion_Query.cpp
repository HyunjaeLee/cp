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
    int N, Q;
    cin >> N >> Q;
    vector<vector<pair<int, int>>> F(Q);
    for (auto i = 0; i < Q; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        --l, --x;
        F[x].emplace_back(l, r);
    }
    vector<int> P(N + 1);
    for (auto f : F) {
        ranges::sort(f);
        vector<pair<int, int>> v;
        for (auto [l, r] : f) {
            if (v.empty() || v.back().second <= l) {
                v.emplace_back(l, r);
            } else {
                v.back().second = max(v.back().second, r);
            }
        }
        for (auto [l, r] : v) {
            P[r]--;
            P[l]++;
        }
    }
    for (auto i = 0; i < N; ++i) {
        P[i + 1] += P[i];
    }
    P.pop_back();
    show(P);
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
