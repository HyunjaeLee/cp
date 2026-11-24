#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint998244353;

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
    int N;
    cin >> N;
    vector<vector<int>> g(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> order;
    {
        vector<vector<int>> ch(g.size());
        [&](this auto &&self, int u, int p) -> void {
            order.push_back(u);
            for (auto v : g[u]) {
                if (v == p)
                    continue;
                self(v, u);
                ch[u].push_back(v);
            }
        }(0, 0);
        swap(g, ch);
    }
    constexpr auto W = 20;
    vector<vector<Z>> dp1(N, vector<Z>(W));
    for (auto u : order | views::reverse) {
        vector<int> max_label(g[u].size());
        vector<vector<optional<Z>>> dp2(size(g[u]));
        for (auto i = 0; i < ssize(g[u]); ++i) {
            for (auto j = 1; j < W; ++j) {
                if (dp1[g[u][i]][j] != 0)
                    max_label[i] = j;
            }
        }
        vector<int> I(g[u].size());
        ranges::iota(I, 0);
        ranges::sort(I, {}, [&](int i) { return max_label[i]; });
        for (auto i = 0; i < ssize(g[u]); ++i) {
            dp2[i].assign(1 << (max_label[I[i]] + 1), nullopt);
        }
        auto f = [&](this auto &&self, int i, int mask) -> Z {
            if (i == -1)
                return mask == 0;
            if (ssize(dp2[i]) <= mask)
                return 0;
            if (dp2[i][mask])
                return *dp2[i][mask];
            auto v = g[u][I[i]];
            Z sum = self(i - 1, mask);
            for (auto j = 1; j <= max_label[I[i]]; ++j) {
                if (((mask >> j) & 1))
                    sum += dp1[v][j] * self(i - 1, mask ^ (1 << j));
            }
            return *(dp2[i][mask] = sum);
        };
        for (auto e = 0; e < W; ++e) {
            if (e == 0) {
                for (auto v : g[u]) {
                    dp1[u][e] += dp1[v][0];
                }
            }
            for (auto i = e; i < W; ++i) {
                auto mask = (1 << (i + 1)) - 2;
                if (e) {
                    assert((mask >> e) & 1);
                    mask ^= 1 << e;
                }
                dp1[u][e] += f(int(g[u].size()) - 1, mask);
            }
        }
    }
    auto ans = dp1[0][0];
    cout << ans.val() << "\n";
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
