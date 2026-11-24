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

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    for (auto i = 0; i < N; ++i) {
        A[i] &= 1;
    }
    vector<vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<vector<int>> g(N);
    vector<int> indegree(N);
    vector<int> color(N);
    auto dfs = [&](this auto &&self, int u, int p) -> int {
        color[u] = 1;
        if (A[u] == 0) {
            return 0;
        }
        auto sz = 1;
        for (auto v : adj[u]) {
            if (v != p) {
                auto a = self(v, u);
                if (a == 0)
                    continue;
                sz += a;
                if (a & 1) {
                    g[u].push_back(v);
                    indegree[v] += 1;
                } else {
                    g[v].push_back(u);
                    indegree[u] += 1;
                }
            }
        }
        return sz;
    };
    for (auto i = 0; i < N; ++i) {
        if (color[i])
            continue;
        auto sz = dfs(i, i);
        if (0 < sz && sz % 2 == 0) {
            cout << "NO\n";
            return;
        }
    }
    queue<int> q;
    for (auto i = 0; i < N; ++i) {
        if (indegree[i] == 0 && A[i] == 1) {
            q.push(i);
        }
    }
    vector<int> ans;
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (auto v : g[u]) {
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
        for (auto v : adj[u]) {
            auto cnt = 0;
            if (A[v] == 0 && color[v]) {
                for (auto x : adj[v]) {
                    if (A[x] == 1 && color[x]) {
                        cnt += 1;
                    }
                }
            }
            if (cnt & 1) {
                color[v] = 0;
                ans.push_back(v + 1);
            }
        }
        color[u] = 0;
        ans.push_back(u + 1);
        for (auto v : adj[u]) {
            auto cnt = 0;
            if (A[v] == 0 && color[v]) {
                for (auto x : adj[v]) {
                    if (A[x] == 1 && color[x]) {
                        cnt += 1;
                    }
                }
            }
            if (cnt & 1) {
                color[v] = 0;
                ans.push_back(v + 1);
            }
        }
    }
    if (int(ans.size()) != N) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
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
