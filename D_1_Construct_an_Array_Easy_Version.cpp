#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N);
    vector<vector<int>> deg(2, vector<int>(N));
    for (auto i = 0; i < M; ++i) {
        int o, u, v;
        cin >> o >> u >> v;
        --o, --u, --v;
        ++deg[o][u];
        ++deg[o][v];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    queue<int> q;
    vector<char> used(N);
    for (auto i = 0; i < N; ++i) {
        if (deg[0][i] == 0 || deg[1][i] == 0) {
            used[i] = true;
            q.push(i);
        }
    }
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        if (q.empty()) {
            cout << "NO\n";
            return;
        }
        auto u = q.front();
        q.pop();
        auto o = deg[1][u] == 0 ? 0 : 1;
        A[u] = (o == 0 ? 1 : -1) * (N - i);
        for (auto v : adj[u]) {
            if (!used[v]) {
                if (--deg[o][v] == 0) {
                    used[v] = true;
                    q.push(v);
                }
            }
        }
    }
    cout << "YES\n";
    for (auto i = 0; i < N; ++i) {
        cout << A[i] << " \n"[i == N - 1];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
