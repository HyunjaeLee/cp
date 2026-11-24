#include <atcoder/dsu>
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
    atcoder::dsu dsu(N);
    vector<vector<int>> G(N);
    vector<pair<int, int>> E(M);
    for (auto &[u, v] : E) {
        cin >> u >> v;
        --u, --v;
        dsu.merge(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    if (dsu.size(0) < N) {
        cout << "NO\n";
        return;
    }
    queue<int> q;
    q.push(0);
    vector<int> color(N, -1);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        if (color[u] != -1)
            continue;
        color[u] = 1;
        for (auto v : G[u]) {
            if (color[v] != -1)
                continue;
            color[v] = 0;
            for (auto x : G[v]) {
                if (color[x] == -1) {
                    q.push(x);
                }
            }
        }
    }
    cout << "YES\n";
    cout << ranges::fold_left(color, 0, plus()) << "\n";
    for (auto i = 0; i < N; ++i) {
        if (color[i]) {
            cout << i + 1 << " ";
        }
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
