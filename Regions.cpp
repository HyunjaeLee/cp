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
    int N, R, Q;
    cin >> N >> R >> Q;
    vector<int> color(N), parent(N, -1);
    cin >> color[0];
    --color[0];
    for (auto i = 1; i < N; ++i) {
        cin >> parent[i] >> color[i];
        --parent[i];
        --color[i];
    }
    vector<vector<int>> F(R); // color -> node
    for (auto i = 0; i < N; ++i) {
        F[color[i]].push_back(i);
    }
    vector<vector<int>> tree(N);
    for (auto i = 1; i < N; ++i) {
        tree[parent[i]].push_back(i);
    }
    vector<int> in(N), out(N);
    auto timer = 0;
    [&](this auto &&self, int u) -> void {
        in[u] = timer++;
        for (auto v : tree[u]) {
            self(v);
        }
        out[u] = timer;
    }(0);
    vector<vector<int>> gin(R), gout(R);
    for (auto i = 0; i < N; ++i) {
        gin[color[i]].push_back(in[i]);
        gout[color[i]].push_back(out[i]);
    }
    for (auto i = 0; i < R; ++i) {
        ranges::sort(gin[i]);
        ranges::sort(gout[i]);
    }
    auto query_subtree = [&](int u, int x) {
        auto r = ranges::lower_bound(gin[x], out[u]);
        auto l = ranges::lower_bound(gin[x], in[u]);
        return r - l;
    };
    auto query_path = [&](int u, int x) {
        auto a = ranges::lower_bound(gin[x], in[u]) - begin(gin[x]);
        auto b = ranges::upper_bound(gout[x], in[u]) - begin(gout[x]);
        return a - b;
    };
    map<pair<int, int>, i64> memo;
    while (Q--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        if (auto it = memo.find({a, b}); it != memo.end()) {
            cout << it->second << endl;
            continue;
        }
        i64 cnt = 0;
        if (size(F[a]) < size(F[b])) {
            for (auto u : F[a]) {
                cnt += query_subtree(u, b);
            }
        } else {
            for (auto v : F[b]) {
                cnt += query_path(v, a);
            }
        }
        memo[{a, b}] = cnt;
        cout << cnt << endl;
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
