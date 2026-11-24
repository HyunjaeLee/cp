#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, T, K;
    cin >> N >> T >> K;
    vector<pair<int, int>> A(N);
    for (auto &[s, e] : A) {
        cin >> s >> e;
    }
    ranges::sort(A);
    vector<vector<pair<int, int>>> G;
    for (auto i = 0; i < N; i += 2 * K) {
        G.emplace_back(A.begin() + i, A.begin() + min(N, i + 2 * K));
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int t, x;
        cin >> t >> x;
        auto it = ranges::lower_bound(G, i64(T) * x, {}, [&](const vector<pair<int, int>> &a) {
            auto [s, e] = a[0];
            return i64(T) * s + i64(e - s) * t;
        });
        auto pos = int(it - G.begin());
        auto p = numeric_limits<i64>::max();
        for (auto i = max(0, pos - 5); i < min(int(G.size()), pos + 5); ++i) {
            for (auto [s, e] : G[i]) {
                p = min(p, abs(i64(T) * s + i64(e - s) * t - i64(T) * x));
            }
        }
        auto g = __gcd<i64>(p, T);
        p = p / g;
        auto q = T / g;
        cout << p << "/" << q << "\n";
    }
}
