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

#define TC
void solve() {
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> rng(M);
    for (auto &[l, r] : rng) {
        cin >> l >> r;
        --l;
    }
    if (N == 1) {
        cout << "0\n";
        return;
    }
    vector<u64> X(N + 1);
    mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());
    for (auto [l, r] : rng) {
        X[l] = X[r] = g();
    }
    for (auto i = 0; i < N; ++i) {
        X[i + 1] ^= X[i];
    }
    vector<pair<int, int>> v;
    for (auto i = 0; i < N; ++i) {
        if (!v.empty() && X[v.back().first] == X[i]) {
            v.back().second++;
        } else {
            v.emplace_back(i, i + 1);
        }
    }
    vector<pair<int, int>> ans;
    vector<pair<int, int>> u;
    auto calc = [&] {
        if (u.size() & 1) {
            auto cnt0 = 0;
            for (auto i = 0; i + 1 < ssize(u); i += 2) {
                auto [l1, r1] = u[i];
                auto [l2, r2] = u[i + 1];
                assert(r1 == l2);
                
            }
        }
        u.clear();
    };
    for (auto [l, r] : v) {
        auto len = r - l;
        if (len <= 1) {
            calc();
        } else {
            u.emplace_back(l, r);
        }
    }
    calc();
    cout << ans.size() << "\n";
    for (auto [l, r] : ans) {
        cout << l << " " << r + 1 << "\n";
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
