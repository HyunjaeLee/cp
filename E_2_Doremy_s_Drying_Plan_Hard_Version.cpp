#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

constexpr auto inf = numeric_limits<int>::max() / 2;
int op(int a, int b) { return max(a, b); }
int e() { return -inf; }

void solve() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> tree(4 * N);
    auto add = [&](auto &&self, int l, int r, int x, int u, int ul, int ur) -> void {
        if (r <= ul || ur <= l)
            return;
        if (l <= ul && ur <= r) {
            tree[u].push_back(x);
            return;
        }
        auto mid = ul + (ur - ul) / 2;
        self(self, l, r, x, 2 * u, ul, mid);
        self(self, l, r, x, 2 * u + 1, mid, ur);
    };
    vector<pair<int, int>> rng(M);
    for (auto i = 0; i < M; ++i) {
        int L, R;
        cin >> L >> R;
        --L;
        rng[i] = {L, R};
        add(add, L, R, i, 1, 0, N);
    }
    vector<int> qs;
    vector<int> S(N);
    vector<vector<int>> R(N);
    auto dfs = [&](auto &&self, int u, int ul, int ur) -> void {
        qs.insert(qs.end(), tree[u].begin(), tree[u].end());
        if (ur - ul == 1) {
            auto p = ul;
            S[p] = int(qs.size());
            if (S[p] <= K) {
                R[p].push_back(p + 1);
                R[p].push_back(N);
                for (auto qid : qs) {
                    R[p].push_back(rng[qid].second);
                }
                ranges::sort(R[p]);
            }
        } else {
            auto mid = ul + (ur - ul) / 2;
            self(self, 2 * u, ul, mid);
            self(self, 2 * u + 1, mid, ur);
        }
        qs.resize(qs.size() - tree[u].size());
    };
    dfs(dfs, 1, 0, N);
    vector<atcoder::segtree<int, op, e>> dp(2 * K + 1, atcoder::segtree<int, op, e>(vector<int>(N, 1)));
    for (auto p = N - 1; 0 <= p; --p) {
        for (auto x = -K; x <= K; ++x) {
            auto need = S[p] + x;
            if (K < S[p] || K < need) {
                dp[K + x].set(p, -inf);
                continue;
            }
            for (auto i = 0; i <= S[p]; ++i) {
                auto l = R[p][i];
                auto r = R[p][i + 1];
                auto y = need - S[p] + i;
                auto val = dp[K + y].prod(l, r);
                dp[K + x].set(p, max(dp[K + x].get(p), 1 + val));
            }
        }
    }
    auto ans = max(0, dp[K].all_prod());
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
