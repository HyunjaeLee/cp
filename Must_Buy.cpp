#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    constexpr auto inf = numeric_limits<i64>::max() / 4;
    int N, M;
    cin >> N >> M;
    vector<int> P(N), V(N);
    for (auto i = 0; i < N; ++i) {
        cin >> P[i] >> V[i];
    }
    vector<vector<i64>> dp(N, vector<i64>(M + 1));
    vector<vector<char>> vis(N, vector<char>(M + 1));
    auto F = [&](auto &&self, int i, int x) -> i64 {
        if (M < x) {
            return -inf;
        }
        if (i == N) {
            return 0;
        }
        auto &ret = dp[i][x];
        if (vis[i][x])
            return ret;
        vis[i][x] = true;
        ret = max(self(self, i + 1, x), V[i] + self(self, i + 1, x + P[i]));
        return ret;
    };
    vector<vector<char>> used(N, vector<char>(M + 1));
    vector<int> A(N);
    auto G = [&](auto &&self, int i, int x) -> void {
        assert(x <= M);
        if (i == N)
            return;
        if (used[i][x])
            return;
        used[i][x] = true;
        auto a = F(F, i + 1, x);
        auto b = V[i] + F(F, i + 1, x + P[i]);
        if (a < b) {
            A[i] |= 1;
            self(self, i + 1, x + P[i]);
        } else if (b < a) {
            A[i] |= 2;
            self(self, i + 1, x);
        } else {
            A[i] |= 3;
            self(self, i + 1, x + P[i]);
            self(self, i + 1, x);
        }
    };
    G(G, 0, 0);
    string S;
    for (auto i = 0; i < N; ++i) {
        if (A[i] == 1) {
            S += 'A';
        } else if (A[i] == 2) {
            S += 'C';
        } else {
            S += 'B';
        }
    }
    cout << S;
}
