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

u64 splitmix64(u64 x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

u64 tree_hash(const vector<vector<int>> &g) {
    auto n = int(g.size());
    auto f = [&](auto &&self, int u, int p) -> u64 {
        static const u64 seed = chrono::steady_clock::now().time_since_epoch().count();
        u64 sum = seed;
        for (auto v : g[u])
            if (v != p)
                sum += self(self, v, u);
        return splitmix64(sum);
    };
    u64 ret = 0;
    auto dfs = [&](auto &&self, int u, int p) -> int {
        auto sz = 1;
        auto is_centroid = true;
        for (auto v : g[u])
            if (v != p) {
                auto ch = self(self, v, u);
                sz += ch;
                is_centroid &= (ch <= n / 2);
            }
        is_centroid &= (n - sz <= n / 2);
        if (is_centroid)
            ret = max(ret, f(f, u, u));
        return sz;
    };
    dfs(dfs, 0, 0);
    return ret;
}

vector<vector<int>> read_tree(int n) {
    vector<vector<int>> g(n);
    for (auto i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return g;
}

#define TC
void solve() {
    int N;
    cin >> N;
    auto f = read_tree(N);
    auto g = read_tree(N);
    cout << (tree_hash(f) == tree_hash(g) ? "YES" : "NO") << "\n";
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
