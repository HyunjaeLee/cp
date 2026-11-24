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
    vector<vector<int>> adj(N);
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (auto r = 0; r < N; ++r) {
        vector<int> parent(N, -1);
        auto x = -1;
        parent[r] = r;
        [&](this auto &&self, int u, int d) -> void {
            auto be = false;
            for (auto v : adj[u]) {
                if (v == r) {
                    be = true;
                }
            }
            if (2 <= d && be && x == -1) {
                x = u;
            }
            for (auto v : adj[u]) {
                if (parent[v] == -1) {
                    parent[v] = u;
                    self(v, d + 1);
                }
            }
        }(r, 0);
        if (x == -1)
            continue;
        vector<int> color(N);
        vector<pair<int, int>> E{pair{x, r}};
        for (auto i = x; i != r; i = parent[i]) {
            color[i] = 1;
            E.emplace_back(i, parent[i]);
        }
        auto cnt = 0;
        for (auto v : adj[r]) {
            if (color[v])
                continue;
            cnt++;
            E.emplace_back(r, v);
            if (cnt == 2)
                break;
        }
        if (cnt < 2)
            continue;
        cout << "YES\n";
        cout << E.size() << "\n";
        for (auto [a, b] : E) {
            cout << a + 1 << " " << b + 1 << "\n";
        }
        return;
    }
    cout << "NO\n";
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
