#include <atcoder/maxflow>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    map<string, u64> H;
    vector<vector<string>> A(N);
    mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());
    for (auto i = 0; i < N; ++i) {
        int k;
        cin >> k;
        A[i].resize(k);
        for (auto &s : A[i]) {
            cin >> s;
            H[s] = g();
        }
    }
    vector<pair<u64, u64>> E;
    for (auto i = 0; i < N; ++i) {
        auto k = int(A[i].size());
        auto hash = [&](int mask) {
            u64 sum = 0;
            for (auto j = 0; j < k; ++j) {
                if ((mask >> j) & 1) {
                    sum ^= H[A[i][j]];
                }
            }
            return sum;
        };
        for (auto s = 1; s < (1 << k); ++s) {
            auto v = hash(s);
            for (auto t = ((s - 1) & s);; t = ((t - 1) & s)) {
                auto u = hash(t);
                E.emplace_back(u, v);
                if (t == 0)
                    break;
            }
        }
    }
    vector<u64> V;
    for (auto [u, v] : E) {
        V.push_back(u);
        V.push_back(v);
    }
    ranges::sort(V);
    V.erase(unique(V.begin(), V.end()), V.end());
    atcoder::mf_graph<int> G(2 * int(V.size()) + 2);
    auto S = 2 * int(V.size());
    auto T = 2 * int(V.size()) + 1;
    for (auto i = 0; i < int(V.size()); ++i) {
        G.add_edge(S, 2 * i, 1);
        G.add_edge(2 * i + 1, T, 1);
    }
    for (auto [u, v] : E) {
        auto x = int(ranges::lower_bound(V, u) - V.begin());
        auto y = int(ranges::lower_bound(V, v) - V.begin());
        G.add_edge(2 * x, 2 * y + 1, 1);
    }
    auto ans = int(V.size()) - G.flow(S, T);
    cout << ans << "\n";
}
