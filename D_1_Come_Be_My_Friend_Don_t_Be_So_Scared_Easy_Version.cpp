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
    assert(M == 0);
    map<int, vector<pair<int, int>>> mp;
    vector<vector<int>> g(4 * N);
    for (auto i = 1; i < N; ++i) {
        g[i].push_back(2 * i);
        g[i].push_back(2 * i + 1);
    }
    auto timer = 0;
    auto dfs = [&](this auto &&self, int u, int d) -> pair<int, int> {
        if (empty(g[u])) {
            auto p = timer++;
            auto l = p, r = p + 1;
            mp[d].emplace_back(l, r);
            return {l, r};
        }
        assert(g[u].size() == 2);
        auto l = self(g[u][0], d + 1).first;
        auto r = self(g[u][1], d + 1).second;
        mp[d].emplace_back(l, r);
        return {l, r};
    };
    dfs(1, 0);
    vector<pair<int, int>> ans;
    for (const auto &[d, v] : mp) {
        vector<pair<int, int>> u;
        for (auto i = 0; i < ssize(v); ++i) {
            auto [l, r] = v[i];
            if (i % 4 == 1) {
                u.emplace_back(l, r);
            } else if (i % 4 == 2) {
                assert(u.back().second == l);
                u.back().second = r;
            }
        }
        ans.insert(ans.end(), u.begin(), u.end());
    }
    cout << ans.size() << "\n";
    for (auto [l, r] : ans) {
        cout << l + 1 << " " << r << "\n";
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
