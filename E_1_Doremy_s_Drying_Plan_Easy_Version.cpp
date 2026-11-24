#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

constexpr i128 P = (1LL << 61) - 1;
constexpr i128 B = 998244353;
const i128 seed = chrono::steady_clock::now().time_since_epoch().count() % P;

i64 H(const vector<int> &v) {
    i128 sum = seed;
    for (auto x : v) {
        sum = (sum * B + x) % P;
    }
    return i64(sum);
}

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
    for (auto i = 0; i < M; ++i) {
        int L, R;
        cin >> L >> R;
        --L;
        add(add, L, R, i, 1, 0, N);
    }
    vector<int> qs;
    unordered_map<i64, int> mp;
    set<vector<int>> S;
    auto dfs = [&](auto &&self, int u, int ul, int ur) -> void {
        qs.insert(qs.end(), tree[u].begin(), tree[u].end());
        if (ur - ul == 1) {
            if (int(qs.size()) <= K) {
                auto v = qs;
                ranges::sort(v);
                S.insert(v);
                ++mp[H(v)];
            }
        } else {
            auto mid = ul + (ur - ul) / 2;
            self(self, 2 * u, ul, mid);
            self(self, 2 * u + 1, mid, ur);
        }
        qs.resize(qs.size() - tree[u].size());
    };
    dfs(dfs, 1, 0, N);
    auto ans = 0;
    for (auto v : S) {
        auto n = int(v.size());
        auto sum = 0;
        for (auto x = 0; x < (1 << n); ++x) {
            i128 u = seed;
            for (auto i = 0; i < n; ++i) {
                if ((x >> i) & 1) {
                    u = (u * B + v[i]) % P;
                }
            }
            sum += mp[i64(u)];
        }
        ans = max(ans, sum);
    }
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
