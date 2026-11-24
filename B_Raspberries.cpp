#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> F(5);
    for (auto i = 0; i < N; ++i) {
        int x;
        cin >> x;
        F[x % K] += 1;
    }
    vector<int> A;
    for (auto i = 0; i < 5; ++i) {
        for (auto j = 0; j < min(2, F[i]); ++j) {
            A.push_back(i);
        }
    }
    N = int(A.size());
    auto bfs = [&] {
        queue<vector<int>> q;
        map<vector<int>, int> dist;
        q.push(A);
        dist[A] = 0;
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            auto prod = 1;
            for (auto i = 0; i < N; ++i) {
                prod = (prod * u[i]) % K;
            }
            if (prod == 0)
                return dist[u];
            for (auto i = 0; i < N; ++i) {
                auto v = u;
                v[i] = (v[i] + 1) % K;
                if (!dist.contains(v)) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return -1;
    };
    auto ans = bfs();
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
