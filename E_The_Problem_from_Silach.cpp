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
    int N, D;
    cin >> N >> D;
    vector<vector<int>> G(2 * N - 1);
    for (auto i = N; i < 2 * N - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        G[i].push_back(a);
        G[i].push_back(b);
    }
    auto root = 2 * N - 2;
    vector<int> depth(2 * N - 1);
    [&](this auto &&self, int u) -> void {
        for (auto v : G[u]) {
            depth[v] = depth[u] + 1;
            self(v);
        }
    }(root);
    vector<int> ans(N);
    for (auto i = 0; i < N; ++i) {
        ans[i] = depth[i];
    }
    [&](this auto &&self, int u) -> priority_queue<int> {
        if (G[u].empty()) {
            priority_queue<int> pq;
            pq.emplace(u);
            return pq;
        }
        auto L = self(G[u][0]);
        auto R = self(G[u][1]);
        if (L.empty()) {
            return R;
        }
        if (R.empty()) {
            return L;
        }
        if (L.top() > R.top()) {
            swap(L, R);
        }
        while (!R.empty() && L.top() + D <= R.top()) {
            auto i = R.top();
            R.pop();
            ans[i] -= depth[u];
        }
        if (L.size() < R.size()) {
            swap(L, R);
        }
        while (!R.empty()) {
            L.push(R.top());
            R.pop();
        }
        return L;
    }(root);
    show(ans);
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
