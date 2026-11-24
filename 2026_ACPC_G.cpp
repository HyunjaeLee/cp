#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int solve(int l, int r, array<int, 30> basis) {
    auto x = 0;
    for (auto i = 29; 0 <= i; --i) {
        auto y = x;
        if (((x >> i) & 1) == 0) {
            y ^= basis[i];
        }
        for (auto j = i - 1; 0 <= j; --j) {
            if (r < y && (y ^ basis[j]) < y) {
                y ^= basis[j];
            }
        }
        if (y <= r) {
            x = y;
        }
    }
    if (l <= x)
        return x;
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;
    vector<int> W(N - 1);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v >> W[i];
    }
    auto timer = 0;
    vector<vector<array<int, 2>>> history(N - 1);
    for (auto i = 0; i < N - 1; ++i) {
        history[i].push_back({timer, W[i]});
    }
    vector<array<int, 2>> query;
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b;
            cin >> a >> b;
            query.push_back({a, b});
            timer++;
        } else {
            int i, w;
            cin >> i >> w;
            --i;
            history[i].push_back({timer, w});
        }
    }
    vector<vector<int>> tree(2 * timer);
    for (auto i = 0; i < N - 1; ++i) {
        for (auto j = 0; j < int(history[i].size()); ++j) {
            auto x = history[i][j][1];
            auto l = history[i][j][0];
            auto r = timer;
            if (j + 1 < int(history[i].size())) {
                r = history[i][j + 1][0];
            }
            l += timer;
            r += timer;
            while (l < r) {
                if (l & 1) {
                    tree[l++].push_back(x);
                }
                if (r & 1) {
                    tree[--r].push_back(x);
                }
                l >>= 1;
                r >>= 1;
            }
        }
    }
    vector<int> ans(timer);
    vector<array<int, 30>> F;
    F.push_back({});
    auto dfs = [&](auto &&self, int node) -> void {
        auto basis = F.back();
        for (auto x : tree[node]) {
            for (auto i = 29; 0 <= i; --i) {
                if ((x >> i) & 1) {
                    if (basis[i]) {
                        x ^= basis[i];
                    } else {
                        basis[i] = x;
                        break;
                    }
                }
            }
        }
        F.push_back(basis);
        if (node < timer) {
            self(self, 2 * node);
            self(self, 2 * node + 1);
        } else {
            auto qid = node - timer;
            auto [a, b] = query[qid];
            ans[qid] = solve(a, b, F.back());
        }
        F.pop_back();
    };
    dfs(dfs, 1);
    for (auto x : ans) {
        cout << x << "\n";
    }
}
