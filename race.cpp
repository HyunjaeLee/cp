#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    auto D = 0;
    vector<vector<int>> g(N);
    for (auto u = 0; u < N; ++u) {
        int d;
        char c;
        cin >> d >> c;
        D = max(D, d);
        for (auto i = 0; i < d; ++i) {
            int v;
            cin >> v;
            g[u].push_back(v);
        }
    }
    vector<int> color(N);
    auto bad = [&](int u) {
        auto cnt = 0;
        for (auto v : g[u]) {
            if (color[u] == color[v]) {
                cnt++;
            }
        }
        return D / 2 < cnt;
    };
    queue<int> q;
    for (auto i = 0; i < N; ++i) {
        if (bad(i)) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        if (!bad(u))
            continue;
        color[u] ^= 1;
        for (auto v : g[u]) {
            if (bad(v)) {
                q.push(v);
            }
        }
    }
    cout << N << "\n";
    for (auto u = 0; u < N; ++u) {
        cout << color[u] << " " << g[u].size() << ": ";
        for (auto v : g[u]) {
            cout << v << " ";
        }
        cout << "\n";
    }
}
