#include <atcoder/modint>
#include <bits/stdc++.h>
#include <immintrin.h>
#pragma GCC target("crc32")
#define MOD 1000000007
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u128 = unsigned __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<vector<int>> adj(N);
    for (auto i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    const auto seed = chrono::steady_clock::now().time_since_epoch().count();
    vector<int> centroids;
    auto dfs = [&](auto &&self, int u, int p) -> int {
        auto acc = 1;
        auto is_centroid = true;
        for (auto v : adj[u]) {
            if (v != p) {
                auto sz = self(self, v, u);
                is_centroid &= sz <= N / 2;
                acc += sz;
            }
        }
        is_centroid &= N - acc <= N / 2;
        if (is_centroid) {
            centroids.push_back(u);
        }
        return acc;
    };
    dfs(dfs, 0, 0);
    vector<i64> fact(N);
    fact[0] = 1;
    for (auto i = 1; i < N; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    i64 ans = 1;
    auto f = [&](auto &&self, int u, int p) -> u64 {
        auto sum = seed;
        unordered_map<u64, int> freq;
        for (auto v : adj[u]) {
            if (v != p) {
                auto h = self(self, v, u);
                sum += h;
                ++freq[h];
            }
        }
        for (auto [k, v] : freq) {
            ans = ans * fact[v] % MOD;
        }
        return _mm_crc32_u64(sum, 0);
    };
    if (centroids.size() == 1) {
        auto c = centroids[0];
        f(f, c, c);
    } else {
        auto c1 = centroids[0];
        auto c2 = centroids[1];
        auto h1 = f(f, c1, c1);
        ans = 1;
        auto h2 = f(f, c2, c2);
        if (h1 == h2) {
            ans = 2 * ans % MOD;
        }
    }
    cout << ans << "\n";
}
