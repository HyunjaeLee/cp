#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

double dp[5050][5050];

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N);
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
    }
    vector<double> P(N);
    P[N - 1] = 1;
    for (auto u = N - 2; 0 <= u; --u) {
        vector<double> a;
        for (auto v : adj[u]) {
            a.push_back(P[v]);
        }
        ranges::sort(a | views::reverse);
        auto k = int(a.size());
        for (auto i = 0; i < k; ++i) {
            P[u] += a[i] * dp[k][i];
        }
    }
    cout << fixed << setprecision(12);
    cout << P[0] << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    dp[1][0] = 1;
    dp[2][0] = 0.5;
    dp[2][1] = 0.0;
    for (auto k = 3; k < 5050; ++k) {
        dp[k][0] = 1.0 / k;
        dp[k][1] = double(k - 2) / k * dp[k - 2][0];
        for (auto i = 2; i < k; ++i) {
            dp[k][i] = double(i - 1) / k * dp[k - 2][i - 2] + double(k - 1 - i) / k * dp[k - 2][i - 1];
        }
    }
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
