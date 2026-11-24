#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<array<double, 2>> A(N);
    for (auto &[x, y] : A) {
        cin >> x >> y;
    }
    auto solve = [&](const vector<array<double, 2>> &P) {
        vector<vector<double>> dp(N, vector<double>(1 << N));
        vector<vector<char>> vis(N, vector<char>(1 << N));
        auto f = [&](auto &&self, int pos, int mask) -> double {
            assert(0 <= pos && pos < N);
            assert((mask >> pos) & 1);
            if (popcount((unsigned)mask) == N) {
                return 0;
            }
            auto &ret = dp[pos][mask];
            if (vis[pos][mask])
                return ret;
            ret = numeric_limits<double>::max();
            vis[pos][mask] = true;
            for (auto i = 0; i < N; ++i) {
                if (((mask >> i) & 1) == 0) {
                    auto dx = abs(P[pos][0] - P[i][0]);
                    auto dy = abs(P[pos][1] - P[i][1]);
                    auto dist = dx + dy;
                    ret = min(ret, dist + self(self, i, mask | (1 << i)));
                }
            }
            return ret;
        };
        auto ans = f(f, 0, 1);
        for (auto i = 1; i < N; ++i) {
            ans = min(ans, f(f, i, 1 << i));
        }
        return ans;
    };
    double ans = numeric_limits<double>::max();
    for (auto i = 0; i < N - 1; ++i) {
        for (auto j = i + 1; j < N; ++j) {
            auto dx = A[j][0] - A[i][0];
            auto dy = A[j][1] - A[i][1];
            auto s = dy / sqrt(dx * dx + dy * dy);
            auto c = dx / sqrt(dx * dx + dy * dy);
            vector<array<double, 2>> P;
            for (auto [x, y] : A) {
                P.push_back({c * x + s * y, -s * x + c * y});
            }
            ans = min(ans, solve(P));
        }
    }
    cout << fixed << setprecision(9);
    cout << ans << "\n";
}
