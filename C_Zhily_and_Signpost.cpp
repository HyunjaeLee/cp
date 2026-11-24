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

i128 Lcm(i128 a, i128 b) { return a * b / __gcd(a, b); }

#define TC
void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<vector<int>> adj(N);
    vector<int> parent(N, -1);
    for (auto i = 1; i < N; ++i) {
        cin >> parent[i];
        --parent[i];
        adj[parent[i]].push_back(i);
    }
    vector<i64> W(N);
    for (auto i = 1; i < N; ++i) {
        cin >> W[i];
    }
    vector<i64> query(Q);
    for (auto &x : query) {
        cin >> x;
    }
    auto X = query;
    ranges::sort(X);
    X.erase(unique(begin(X), end(X)), end(X));
    unordered_map<i64, int> ans;
    constexpr auto inf = numeric_limits<i64>::max() / 2;
    [&](this auto &&self, int u, i64 dist, i64 acc, vector<i64> ts) -> void {
        if (ts.empty())
            return;
        if (adj[u].empty()) {
            for (auto t : ts) {
                ans[t] = u;
            }
            return;
        }
        auto d = ssize(adj[u]);
        vector<vector<i64>> g(d);
        if (inf <= acc || acc == Lcm(acc, d)) {
            g[(dist + ts[0]) % d] = std::move(ts);
        } else {
            for (auto t : ts) {
                g[(dist + t) % d].push_back(t);
            }
        }
        for (auto [i, v] : views::enumerate(adj[u])) {
            self(v, dist + W[v], (i64)min<i128>(inf, Lcm(acc, d)), std::move(g[i]));
        }
    }(0, 0, 1, std::move(X));
    for (auto x : query) {
        assert(ans.contains(x));
        cout << ans[x] + 1 << " ";
    }
    cout << "\n";
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
