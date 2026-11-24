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
    int N;
    cin >> N;
    vector<vector<pair<int, int>>> adj(N);
    for (auto i = 1; i < N; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }
    vector<int> A(N), parent(N);
    [&](this auto &&self, int u) -> void {
        for (auto [v, i] : adj[u]) {
            if (v == parent[u])
                continue;
            A[v] = i;
            parent[v] = u;
            self(v);
        }
    }(0);
    auto ans = 1 + [&](this auto &&self, int u) -> int {
        auto ret = 0;
        for (auto [v, i] : adj[u]) {
            if (v == parent[u])
                continue;
            auto cnt = self(v);
            if (A[u] > A[v]) {
                cnt++;
            }
            ret = max(ret, cnt);
        }
        return ret;
    }(0);
    cout << ans << "\n";
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
